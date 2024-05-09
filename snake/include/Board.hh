/*
 * View
*/
#pragma once
#include "Drawable.hh"

class Board {
public:
    Board() {}
    Board(const int height, const int width): 
        H(height), W(width) {
        
        int hScreen, wScreen;
        getmaxyx(stdscr, hScreen, wScreen);
        // 游戏板放在中心，所以 屏幕的中心坐标 要做偏移
        board_win = newwin(height, width, hScreen/2-height/2, wScreen/2-width/2);

        wtimeout(board_win, 1000); // timeout: ms
        keypad(board_win, true);   // also use arrow key
    }
    
    void initialize() {
        clear();
        refresh();
    }

    void addBorder() { box(board_win, 0, 0); }
    
    void add(const Drawable d) { addAt(d.getH(), d.getW(), d.getGoods()); }
    // index from 0
    void addAt(int h, int w, chtype ch) { mvwaddch(board_win, h, w, ch); }  // mv window add char
    
    chtype getCharAt(const int y, const int x) { return mvwinch(board_win, y, x); }

    void getEmptyCoordinate(int &h, int &w) {
        while (mvwinch(board_win, h, w) != ' ') {
            h = rand() % H;
            w = rand() % W;
        }
    }

    chtype getInput() { return wgetch(board_win); }
    void setTimeout(int t) { wtimeout(board_win, t); }

    void clear() {
        wclear(board_win);
        addBorder();
    }
    void refresh() { wrefresh(board_win); }

private:
    WINDOW *board_win;
    int H, W;
};