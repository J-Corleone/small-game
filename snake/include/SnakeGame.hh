#pragma once
#include <ctime>
#include <cstdlib>
#include "board.hh"
#include "Snake.hh"

class SnakeGame {
public:
    ~SnakeGame() { delete apple; }

    SnakeGame(const int h, const int w):
        game_over(false), board(Board(h, w)), apple(NULL) {

        srand(time(NULL));
        board.initialize();

        // Snake init
        SnakePiece next(h/2, w/2);
        board.add(next);
        snake.addPiece(next);

        snake.setDirect(UP);
        next = snake.nextHead();
        board.add(next);
        board.add(snake.headToBody());
        snake.addPiece(next);

        next = snake.nextHead();
        board.add(next);
        board.add(snake.headToBody());
        snake.addPiece(next);
    }

    void processInput() {
        chtype input = board.getInput();
        // process
    }
    
    void updateState() {
        // generate Apple
        if (apple == nullptr) {
            int h, w;
            board.getEmptyCoordinate(h, w);
            apple = new Apple(h, w);
            board.add(*apple);
        }

        SnakePiece next(snake.nextHead());
        // when not encounter 🍎, remove 🐍 tail.
        if (next.getH() != apple->getH() || next.getW() != apple->getW()) {
            SnakePiece emptyPiece(snake.tail());
            board.add(Drawable().reEmpty(emptyPiece.getH(), emptyPiece.getW()));
            snake.rmvPiece();
        }
        
        board.add(next);
        board.add(snake.headToBody());
        snake.addPiece(next);
    }
    
    void redraw() {
        board.refresh();
    }

    bool isOver() const { return game_over; }

private:
    bool game_over;
    Board board;
    Apple *apple;
    Snake snake;
};