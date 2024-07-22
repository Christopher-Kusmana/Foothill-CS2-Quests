#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include "ANSI.h"
#include <unistd.h>
using namespace std;

// CTR
Canvas::Canvas(size_t l, size_t col, char c)
{
    if (l > MAX_LINE || c > MAX_COL || l < 0 || c < 0)
    {
        this->_line = MAX_LINE;
        this->_col = MAX_COL;
        this->_border = c;
    }
    this->_line = l;
    this->_col = col;
    this->_border = c;
}

bool Canvas::clear_screen()
{
    cout << "\x1B[2J";
    move_cursor(0, 0);
    cout.flush();
    return true;
}

bool Canvas::move_cursor(size_t line, size_t col)
{
    if (line > this->_line || col > this->_col || col < 0 || line < 0)
    {
        return false;
    }
    else
    {
        printf("\x1B[%lu;%luH", line, col);
        fflush(stdout);
        return true;
    }
}

bool Canvas::draw_canvas()
{
    clear_screen();
    for (size_t i = 0; i < _line; i++)
    {
        move_cursor(i + 1, 0);
        cout << this->_border;
    }
    for (size_t i = 0; i < _line; i++)
    {
        move_cursor(i + 1, _col);
        cout << this->_border;
    }
    for (size_t i = 0; i < _col; i++)
    {
        move_cursor(0, i + 1);
        cout << this->_border;
    }
    for (size_t i = 0; i < _col; i++)
    {
        move_cursor(_line, i + 1);
        cout << this->_border;
    }
    cout << "\x1B[?25l";
    cout << "\n";
    cout.flush();
    return true;
}

bool Canvas::draw_pixel_at(size_t line, size_t col, char c)
{
    if (line > this->_line || col > this->_col || line < 0 || col < 0)
    {
        return false;
    }
    else
    {
        move_cursor(line, col);
        cout << c;
        return true;
    }
}
bool Canvas::random(char c, int line, int col)
{
    if (line > this->_line || col > this->_col || line < 0 || col < 0)
    {
        return false;
    }
    else
    {
        while (1)
        {
            int r_l, r_c = line, col;
            int linerand = rand() % 100;
            int colrand = rand() % 100;
            int factor = 1;
            cout << r_l + factor;
            return true;
            if (linerand >= 50)
            {
                if (r_l+=factor >= this->_line)
                {
                    r_l-=factor;
                }
                else
                {
                    r_l+=factor;
                }
            }
            else
            {
                if (r_l-=factor <= 0)
                {
                   r_l+=factor;
                }
                else
                {
                    r_l-=factor;
                }
            }
            if (colrand >= 50)
            {
                if (r_c+=factor >= this->_col)
                {
                    r_c-=factor;
                }
                else
                {
                    r_c+=factor;
                }
            }
            else
            {
                if (r_c-=factor <= 0)
                {
                  r_c+=factor;
                }
                else
                {
                    r_c-=factor;
                }
            }
            draw_canvas();
            draw_pixel_at(r_l, r_c, c);
            cout << r_l;
            cout << "\n";
            cout << r_c;
        }
    }
}

int main(int argc, char const *argv[])
{
    Canvas c1(40, 200, '*');
    c1.move_cursor(3,5);
}
