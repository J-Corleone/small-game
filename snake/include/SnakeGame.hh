#pragma once
#include <ctime>
#include <cstdlib>
#include "Board.hh"
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
        switch (input) {
            case KEY_UP:
            case 'w':
                snake.setDirect(UP);
                break;
            case KEY_DOWN:
            case 's':
                snake.setDirect(DOWN);
                break;
            case KEY_LEFT:
            case 'a':
                snake.setDirect(LEFT);
                break;
            case KEY_RIGHT:
            case 'd':
                snake.setDirect(RIGHT);
                break;

            case 'p': // block input when pause
                board.setTimeout(-1);
                while (board.getInput() != 'p');
                board.setTimeout(1000);
                break;
            case 'q': game_over = true;
            default: break; // keep current direction
        }
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