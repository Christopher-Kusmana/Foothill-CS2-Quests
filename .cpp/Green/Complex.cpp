// Student ID: 20527001

#include "Complex.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

bool Complex::operator==(const Complex &that) const
{
    return this->_real == that._real && this->_imag == that._imag;
}

bool Complex::operator<(const Complex &that) const
{
    return this->norm_squared() < that.norm_squared();
}

Complex Complex::operator+(const Complex &that) const
{
    Complex res(this->_real + that._real, this->_imag + that._imag);
    return res;
}

Complex Complex::operator-(const Complex &that) const
{
    Complex res(this->_real - that._real, this->_imag - that._imag);
    return res;
}

Complex Complex::operator*(const Complex &that) const
{
    Complex res((this->_real * that._real) - (this->_imag * that._imag), (this->_real * that._imag) + (this->_imag * that._real));
    return res;
}

Complex Complex::reciprocal() const
{

    if (this->norm_squared() <= Complex::FLOOR)
    { // watch for round-off
        throw Div_By_Zero_Exception();
    }
    Complex res((this->_real) / this->norm_squared(), -1 * ((this->_imag) / this->norm_squared()));
    return res;
}

Complex Complex::operator/(const Complex &that) const
{
    return *this * that.reciprocal();
}

string Complex::to_string() const
{
    char buf[100];
    sprintf(buf, "(%.11g,%.11g)", _real, _imag);
    return string(buf);
}

Complex &Complex::operator=(const Complex &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    _real = rhs._real;
    _imag = rhs._imag;

    return *this;
}