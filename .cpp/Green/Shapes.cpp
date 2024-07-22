// Student ID: 20527001
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "Shapes.h"
using namespace std;

Screen::Screen(size_t w, size_t h)
{
    set_w(w);
    set_h(h);
    _pix.resize(h);
    for (auto &row : _pix)
    {
        row.resize(w);
    }
}

void Screen::fill(char c)
{
    for (auto &row : _pix)
    {
        std::fill(row.begin(), row.end(), c);
    }
}

string Screen::to_string() const
{

    string result;
    for (auto it = _pix.crbegin(); it != _pix.crend(); ++it)
    {
        for (auto c : *it)
        {
            result += c;
        }
        result += '\n';
    }
    return result;
}

bool Point::draw(Screen &screen, char c)
{
    size_t h = screen.get_h();
    size_t w = screen.get_w();
    if (_y < h && _x < w)
    {
        screen.get_pix()[_y][_x] = c;
        return true;
    }
    return false;
}

bool Line::draw_by_x(Screen &scr, char ch, size_t x1, size_t y1, size_t x2, size_t y2)
{
    if (x1 > x2)
    {
        return draw_by_x(scr, ch, x2, y2, x1, y1);
    }

    double dy = ((double)y2 - y1) / ((double)x2 - x1);
    bool contained = true;
    double x = x1, y = y1;
    while (x <= x2)
    {
        contained &= Point((size_t)x, (size_t)y).draw(scr, ch);
        x += 1;
        y += dy;
    }
    return contained;
}

bool Line::draw_by_y(Screen &scr, char ch, size_t x1, size_t y1, size_t x2, size_t y2)
{
    if (y1 > y2)
    {
        return draw_by_y(scr, ch, x2, y2, x1, y1);
    }

    double dx = ((double)x2 - x1) / ((double)y2 - y1);
    bool contained = true;
    double x = x1, y = y1;
    while (y <= y2)
    {
        contained &= Point((size_t)x, (size_t)y).draw(scr, ch);
        y += 1;
        x += dx;
    }
    return contained;
} // Discussion in sub

bool Line::draw(Screen &screen, char c)
{
    size_t dx = abs((int)_x2 - (int)_x1);
    size_t dy = abs((int)_y2 - (int)_y1);

    if (dx > dy)
    {
        return draw_by_x(screen, c, _x1, _y1, _x2, _y2);
    }
    else
    {
        return draw_by_y(screen, c, _x1, _y1, _x2, _y2);
    }
}

bool Quadrilateral::draw(Screen &screen, char c)
{
    Line line1(_x1, _y1, _x2, _y2);
    Line line2(_x2, _y2, _x3, _y3);
    Line line3(_x3, _y3, _x4, _y4);
    Line line4(_x4, _y4, _x1, _y1);

    bool contained = true;
    contained &= line1.draw(screen, c);
    contained &= line2.draw(screen, c);
    contained &= line3.draw(screen, c);
    contained &= line4.draw(screen, c);

    return contained;
}

Stick_Man::Stick_Man(size_t x, size_t y, size_t w, size_t h)
{

    _parts.clear();
    _x = x;
    _y = y;
    _w = (w == 0 || w == 1) ? 20 : w;
    _h = (h == 0 || h == 1) ? 40 : h;


    _parts.push_back(new Upright_Rectangle(x, y + _h / 2, x + _w - 1, y + _h - 1));
    _parts.push_back(new Line(x + _w / 2, y + _h / 2, x + _w / 2, y + _h / 4));
    _parts.push_back(new Line(x + _w / 2, y + _h / 2, x + _w / 4, y + _h / 4));
    _parts.push_back(new Line(x + _w / 2, y + _h / 2, x + 3 * _w / 4, y + _h / 4));
    _parts.push_back(new Line(x + _w / 2, y + _h / 4, x, y));
    _parts.push_back(new Line(x + _w / 2, y + _h / 4, x + _w - 1, y));
}

bool Stick_Man::draw(Screen &screen, char c)
{
    bool contained = true;
    for (auto shape : _parts)
    {
        contained &= shape->draw(screen, c);
    }
    return contained;
}

Stick_Man::~Stick_Man()
{
    for (auto shape : _parts)
    {
        delete shape;
    }
    _parts.clear();
}