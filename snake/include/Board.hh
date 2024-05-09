/*
 * View
*/
#pragma once
#include "Drawable.hh"
#include "Time.hh"

class Board {
public:
    Board() {}
    Board(const int height, const int width, const int speed): 
        H(height), W(width), Timeout(speed) {
        
        int hScreen, wScreen;
        getmaxyx(stdscr, hScreen, wScreen);
        // 游戏板放在中心，所以 屏幕的中心坐标 要做偏移
        start_row = hScreen/2-height/2;
        start_col = wScreen/2-width/2;
        board_win = newwin(height, width, start_row, start_col);

        setTimeout(speed);
        keypad(board_win, true);   // also use arrow key
    }
    
    void initialize() {
        clear();
        refresh();
    }
    // 加边框
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

    chtype getInput() {
        time_t st_time = Time::getTime();

        chtype input = wgetch(board_win);
        chtype new_input = ERR;

        // 保证在 时延 之前不更新游戏状态
        setTimeout(0);
        while (st_time + Timeout >= Time::getTime())
            new_input = wgetch(board_win);
        setTimeout(Timeout);
        
        // 以 时延 内最后一个输入为准
        if (new_input != ERR) input = new_input;

        return input;
    }

    void setTimeout(const int t) { wtimeout(board_win, t); }
    int getTimeout() const { return Timeout; }

    void clear() {
        wclear(board_win);
        addBorder();
    }
    void refresh() { wrefresh(board_win); }

    // display Game Over
    void display() {
        /**
         * "xxx" is const, constexpr只是字面量，没有 const 的不变性
         * so it should be: constexpr const char *s
         *                 or
         *                  constexpr char s[]
        */
        constexpr const char *s = "Game Over!";
        // 带边框，3行12列
        WINDOW *finish_win = newwin(3, 12, start_row + H/2 - 2, start_col + W/2 - 6);
        box(finish_win, 0, 0);
        mvwprintw(finish_win, 1, 1, s);
        wrefresh(finish_win);
    }

private:
    WINDOW *board_win;
    // board's H and W; draw at (row, col) of screen.
    int H, W, start_row, start_col;
    int Timeout;
};