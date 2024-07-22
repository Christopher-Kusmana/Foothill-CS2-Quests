// Student ID: 20527001
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef HANOI_H
#define HANOI_H
class Hanoi
{
private:
    std::vector<std::vector<std::vector<std::string>>> _cache;       // cache for storing previous function calls
    std::string get_moves(int num_discs, int src, int dst, int tmp); // recursive function for calculating moves
    std::string lookup_moves(int num_discs, int src, int dst) const; // function for looking up moves in the cache
    

public:
    // Use freebie default constructor

    std::string solve(int num_discs, int src, int dst, int tmp); // public function for solving the problem
    friend class Tests;                                          // Don't remove this line
};

#endif