#pragma once
#include <raymath.h>
#include <deque>
#include "common.hh"

class Apple {
    Vector2 pos;
    Texture2D texture;
public:
    Apple() {
        Image img = LoadImage("img/apple.png");
        ImageResize(&img, cellSz-2, cellSz-2);  // resize, my img too large
        texture = LoadTextureFromImage(img);

        creatApple();

        UnloadImage(img);
    }
    // 会报段错误，应该是啥时候释放过了
    // ~Apple() { UnloadTexture(texture);cout << "~Apple()\n"; }


    // 坐标，宽高 都要乘grid的大小; WHITE: 用原本的颜色
    void Draw() { DrawTexture(texture, pos.x*cellSz + offset, pos.y*cellSz + offset, WHITE); }

    void creatApple() {
        float x = GetRandomValue(0, cellCnt-1);
        float y = GetRandomValue(0, cellCnt-1);
        pos = {x, y};
    }

    Vector2 getPos() const { return pos; }
};

enum Direct {
    UP = -1, DOWN = 1,
    LEFT = -2, RIGHT = 2,
};

class Snake {
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direc{1, 0};
    Direct cur_direc = RIGHT;
    bool canEat = false;
public:
    void Draw() {
        for (auto &p: body){
            float x = p.x;
            float y = p.y;
            Rectangle rec{x*cellSz + offset, y*cellSz + offset, cellSz, cellSz};
            DrawRectangleRounded(rec, 0.5, 6, darkGreen);
        };
    }

    void mvSnake() {
        body.push_front(Vector2Add(body[0], direc));

        if (canEat == true)
            canEat = false;
        else
            body.pop_back();
    }

    Vector2 getHead() const { return body[0]; }
    void Eat() { canEat = true; }

    bool is_SnakeBody(const Vector2 a, const int withhead = 1) const {
        for (uint i=withhead?0:1; i < body.size(); ++i) {
            if (body[i].x == a.x && body[i].y == a.y) return true;
        }
        return false;
    }

    void setDirect(const Direct d) {
        if (cur_direc + d != 0) {
            cur_direc = d;
            switch (d) {
                case UP: direc = {0, -1}; break;
                case DOWN: direc = {0, 1}; break;
                case LEFT: direc = {-1, 0}; break;
                case RIGHT: direc = {1, 0}; break;
            }
        }
        // 相反的方向是 invalid
    }
};

