#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
using namespace std;
#ifndef ANSI_H
#define ANSI_H

class Canvas{
    private:
        size_t _line, _col; 
        char _border;

    public:
        Canvas(size_t l, size_t col, char c);
        static const int MAX_LINE = 40;
        static const int MAX_COL = 156;
        bool clear_screen();
        bool draw_canvas();
        bool draw_pixel_at(size_t row, size_t col, char c);
        bool remove_pixel_at(size_t row, size_t col);
        bool draw_line(size_t x1, size_t x2, size_t y1, size_t y2);
        //Helper
        bool move_cursor(size_t x, size_t y);
        bool random(char c, int line, int col);
};

#endif