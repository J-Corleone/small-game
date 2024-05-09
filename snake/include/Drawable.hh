#pragma once

#include <ncurses.h>

class Drawable {
 public:
  Drawable(): h(0), w(0), goods(' ') {}
  Drawable(const int h, const int w, const chtype ch): h(h), w(w), goods(ch) {}

  Drawable reEmpty(int h, int w) {
    this->h = h;
    this->w = w;
    // this->goods = ' ';
    return *this;
  }

  int getH() const { return h; }
  int getW() const { return w; }
  chtype getGoods() const { return goods; }

 protected:
  int h, w;
  chtype goods;
};

class Apple: public Drawable {
public:
  Apple(int h, int w) {
    this->h = h;
    this->w = w;
    this->goods = 'O';
  }
};

