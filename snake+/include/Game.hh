#pragma once
#include "Model.hh"

static double lastUpdateTime = 0;
bool eventTriggered(const double intv) {
    double curTime = GetTime();
    if (curTime - lastUpdateTime >= intv) {
        lastUpdateTime = curTime;
        return true;
    }
    return false;
}

class SnakeGame {
    Apple apple;
    Snake snake;
    uint score = 0;
    bool running = true;

    Sound eatSound, crashSound;

public:
    SnakeGame() {
        InitAudioDevice();
        eatSound = LoadSound("audio/eat.mp3");
        crashSound = LoadSound("audio/crash.mp3");
    }
    ~SnakeGame() {
        UnloadSound(eatSound);
        UnloadSound(crashSound);
        CloseAudioDevice();
    }

    void Draw() {
        snake.Draw();
        apple.Draw();
    }

    void prcsInput() {
        int key = GetKeyPressed();
        switch (key) {
            case KEY_W:
            case KEY_UP: snake.setDirect(Direct::UP);
                break;
            case KEY_S:
            case KEY_DOWN: snake.setDirect(Direct::DOWN);
                break;
            case KEY_A:
            case KEY_LEFT: snake.setDirect(Direct::LEFT);
                break;
            case KEY_D:
            case KEY_RIGHT: snake.setDirect(Direct::RIGHT);
                break;

            // 重新游戏，只有在结束的时候有效
            case KEY_R: if (!running) reset(); break;
        }
    }

    void updateState() {
        if (running == false) return;

        // set timeout
        if (eventTriggered(0.1))
            snake.mvSnake();

        checkFood();
        checkCollision();
    }

    void checkFood() {
        if (Vector2Equals(snake.getHead(), apple.getPos()) == false) return;
        
        snake.Eat();

        ++score;
        PlaySound(eatSound);
    
        do {
            // 防止生成的🍎和🐍重叠
            // 不能根据颜色判断生成位置，这时候还没有画新蛇头
            apple.creatApple();
        } while (snake.is_SnakeBody(apple.getPos()));
    }

    void checkCollision() {
        Vector2 head = snake.getHead();
        if (snake.is_SnakeBody(head, 0) ||
            head.x < 0 || head.y < 0 ||
            head.x >= cellCnt || head.y >= cellCnt) {
            
            isOver();
            
        }
            
    }

    uint getScore() const { return score; }

    void isOver() {
        running = false;
        PlaySound(crashSound);
    }

    void reset() {
        snake = Snake();
        running = true;
        score = 0;
    }
};