// Student ID: 20527001
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{

private:
    double _real, _imag;

public:
    static constexpr double FLOOR = 1e-10; // Treshold

    Complex(double re = 0.0, double im = 0.0)
    {
        _real = re;
        _imag = im;
    }
    double get_real() { return _real; }
    double get_imag() { return _imag; }
    void set_real(double re) { _real = re; }
    void set_imag(double im) { _imag = im; }
    string to_string() const;
    double norm_squared() const { return _real * _real + _imag * _imag; }
    double norm() { return sqrt(norm_squared()); }
    Complex reciprocal() const;
    Complex &operator=(const Complex &rhs);
    class Div_By_Zero_Exception
    {
    public:
        string what(){return "Divide by zero exception";}
        string to_string(){return "Divide by zero exception";}
    };

    Complex operator+(const Complex &that) const;
    Complex operator-(const Complex &that) const;
    Complex operator*(const Complex &that) const;
    Complex operator/(const Complex &that) const;

    bool operator==(const Complex &that) const;
    bool operator!=(const Complex &that) const { return !(*this == that); };
    bool operator<(const Complex &that) const;

    friend ostream &operator<<(ostream &os, const Complex &x) {os << x.to_string(); return os;}
    friend class Tests;
};

#endif