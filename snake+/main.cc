#include "include/common.hh"
#include "include/Model.hh"
#include "include/Game.hh"

int main() {
    // 750 x 750 px, 外边有边框
    InitWindow(cellSz * cellCnt + offset*2, cellSz * cellCnt + offset*2, "Game");
    Rectangle rec = {offset-5, offset-5, cellSz * cellCnt + 10, cellSz * cellCnt + 10};
    SetTargetFPS(60);   // 以固定的速度运行游戏

    SnakeGame game;
    // 检查是否按了 <Esc> 或关闭窗口
    while (WindowShouldClose() == false) {
        BeginDrawing();

        // 1: Event Handle
        game.prcsInput();
        
        // 2: Update State
        game.updateState();
        
        // 3: Draw
        ClearBackground(green);
        DrawRectangleLinesEx(rec, 5, darkGreen);
        DrawText("iEat Snake", offset-5, 2, 40, darkGreen);
        DrawText(TextFormat("Score: %i", game.getScore()), cellSz*cellCnt-offset*2, 2, 40, darkGreen);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}