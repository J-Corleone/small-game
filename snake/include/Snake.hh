#pragma once
#include <ncurses.h>
#include <queue>
#include "Drawable.hh"

enum Direct {
    NONE,
    // make it easy to check valid direction
    UP = -1, DOWN = 1,
    LEFT = -2, RIGHT = 2
};

class SnakePiece: public Drawable {
public:
    SnakePiece() {
        this->h = this->w = 0;
        this->goods = '@';
    }

    SnakePiece(int h, int w) {
        this->h = h;
        this->w = w;
        this->goods = '@';
    }

    void setBody() { this->goods = '#'; }
};

class Snake {
public:
    Snake() { cur_direct = NONE; }
    
    void addPiece(SnakePiece piece) { body.push(piece); }
    void rmvPiece() { body.pop(); }

    Direct getDirect() const { return cur_direct; }
    void setDirect(const Direct d) {
        // can't go opposite direction
        if (cur_direct + d != 0)
            cur_direct = d;
    }

    SnakePiece nextHead() {
        int row = head().getH();
        int col = head().getW();
        switch (cur_direct) {
            case UP: --row; break;
            case DOWN: ++row; break;
            case LEFT: --col; break;
            case RIGHT: ++col; break;
        }
        return SnakePiece(row, col);
    }

    // queue head is Snake tail, Snake head likewise.
    SnakePiece tail() const { return body.front(); }
    SnakePiece head() const { return body.back(); }
    
    // #***@ --> #***#@
    SnakePiece headToBody() {
        // 这里不能调用 head, 因为它返回的不是引用，只是一个副本；而且 引用和const 不能共存
        body.back().setBody();
        return body.back();
    }

private:
    std::queue<SnakePiece> body;
    Direct cur_direct;
};