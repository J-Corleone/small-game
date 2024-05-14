#include <raylib.h>
#include <raymath.h>

using namespace std;
#define ADD 200

const Color green = {38, 185, 154, 255};
const Color darkgreen = {20, 160, 133, 255};
const Color lightgreen = {129, 204, 184, 255};
const Color yellow = {243, 213, 91, 255};

const int Screen_W = 1280;
const int Screen_H = 800;

const int paddle_W = 25;
const int paddle_H = 120;

static int score1, score2;

class Ball {
public:
    Vector2 pos = {Screen_W/2, Screen_H/2}, speed = {-2, 3};
    float radius = 15;

    void Draw() {
        DrawCircle(pos.x, pos.y, radius, yellow);
    }
    
    void update() {
        pos = Vector2Add(pos, speed);

        // 🥎撞墙
        if (pos.y+radius >= Screen_H || pos.y-radius <= 0) {
            speed.y *= -1;
        }
        if (pos.x+radius >= Screen_W || pos.x-radius <= 0) {
            speed.x *= -1;
            if (pos.x+radius >= Screen_W)
                ++score1;
            else ++score2;
        }
            
    }
};

class Paddle {
public:
    Rectangle rec;
    int speed = 2;

    Paddle(Vector2 p) {
        rec.x = p.x;
        rec.y = p.y;
        rec.width = paddle_W;
        rec.height = paddle_H+ADD;
    }

    void Draw() {
        DrawRectangleRounded(rec, 0.8, 0, WHITE);
    }
    void update() {
        // 非阻塞的检查按键
        if (IsKeyDown(KEY_UP))
            rec.y -= speed;
        if (IsKeyDown(KEY_DOWN))
            rec.y += speed;
        
        edge_chk(rec.y, rec.height);
    }
    void edge_chk(float &y, float &szy) {
        if (y <= 0) y = 0;
        if (y + szy >= Screen_H) y = Screen_H - szy;
    }
};

class AIPaddle : public Paddle {
public:
    // 委托构造
    AIPaddle(Vector2 p): Paddle(p) { rec.height-=ADD; }

#ifdef PONG_PVP
    // 玩家2控制
    void update(Ball &b) {
        // 非阻塞的检查按键
        if (IsKeyDown(KEY_W))
            rec.y -= speed;
        if (IsKeyDown(KEY_S))
            rec.y += speed;
        
        edge_chk(rec.y, rec.hight);
    }
#else // 电脑控制
    void update(Ball &b) {
        if (b.speed.x <0) { // 往它的方向去才动

            if (rec.y+rec.height/2 < b.pos.y)
                rec.y += speed;
            else
                rec.y -= speed;
            
            edge_chk(rec.y, rec.height);
        }
    }
#endif
};

int main() {
    InitWindow(Screen_W, Screen_H, "PONG!");

    Ball ball;
    Paddle pd1({Screen_W-paddle_W-10, (Screen_H-paddle_H)/2});
    AIPaddle pd2({10, (Screen_H-paddle_H)/2});

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // 1: event handle
        if (CheckCollisionCircleRec(ball.pos, ball.radius, pd1.rec) ||
            CheckCollisionCircleRec(ball.pos, ball.radius, pd2.rec))
            ball.speed.x *= -1;

        // 2: update state
        ball.update();
        pd1.update();
        pd2.update(ball);

        // 3: draw
        ClearBackground(lightgreen);
        DrawCircle(Screen_W/2, Screen_H/2, 150, darkgreen);
        DrawLine(Screen_W/2, 0, Screen_W/2, Screen_H, WHITE);
        ball.Draw();
        pd1.Draw();
        pd2.Draw();
        DrawText(TextFormat("P1-%i", score1), Screen_W/4 -50, 20, 80, WHITE);
        DrawText(TextFormat("P2-%i", score2), 3*Screen_W/4 -50, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}