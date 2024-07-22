// Student ID: 20527001
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
#include "Pivoting.h"
using namespace std;


void my_questing_sort_in_place_helper(std::vector<int> &elems, int start, int end)
{
    if (start >= end)
    {
        return; 
    }
    int pivot = elems[(start + end) / 2];

    int i = start;
    int j = end;
    while (i <= j)
    {
        while (elems[i] < pivot)
        {
            i++;
        }
        while (elems[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            std::swap(elems[i], elems[j]);
            i++;
            j--;
        }
    }
    my_questing_sort_in_place_helper(elems, start, j);
    my_questing_sort_in_place_helper(elems, i, end);
}

void my_questing_sort_in_place(std::vector<int> &elems)
{
    my_questing_sort_in_place_helper(elems, 0, elems.size() - 1);
}


