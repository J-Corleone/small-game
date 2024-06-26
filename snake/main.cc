#include <iostream>
#include "include/Board.hh"
#include "include/SnakeGame.hh"

using namespace std;

#define BOARD_DIM 20
#define BOARD_H BOARD_DIM
#define BOARD_W BOARD_DIM * 2.5

int main(int argc, char *argv[]) {

    initscr();
    refresh();
    noecho();    // dont display user input
    curs_set(0); // Also curser

    SnakeGame game(BOARD_H, BOARD_W, 100);

    while (!game.isOver()) {
        // 1: get input from user
        game.processInput();
        // 2: update game state
        game.updateState();
        // 3: redraw
        game.redraw();
    }
    game.Over();
    while (getch() != ' '); // type ' ' to quit
    
    endwin();

    return 0;
}