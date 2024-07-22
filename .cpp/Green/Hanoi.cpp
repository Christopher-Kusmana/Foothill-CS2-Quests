// Student ID: 20527001

#include "Hanoi.h"
#include <vector>
#include <time.h>
using namespace std;

string Hanoi::get_moves(int num_discs, int src, int dst, int tmp)
{

    if (num_discs >= static_cast<int>(_cache.size()))
    {
        _cache.resize(num_discs + 1);
    }
    if (src >= static_cast<int>(_cache[num_discs].size()))
    {
        _cache[num_discs].resize(src + 1);
    }
    if (dst >= static_cast<int>(_cache[num_discs][src].size()))
    {
        _cache[num_discs][src].resize(dst + 1);
    }
    string moves = "";
    moves = lookup_moves(num_discs, src, dst);
    if (!moves.empty())
    {
        return moves;
    }
    if (num_discs == 0)
    {
        return moves;
    }
    if (num_discs == 1)
    {

        moves += to_string(src) + "->" + to_string(dst) + "\n";
        _cache[num_discs][src][dst] = moves;
        return moves;
        // if (src == 1 && dst == 2)
        // { // case 1: move 1 disc from pole 1 to pole 2

        //     moves += "1->2\n";
        //     return moves;
        // }
        // if (src == 1 && dst == 3)
        // { // case 2: move 1 disc from pole 1 to pole 3
        //     moves += "1->3\n";
        //     return moves;
        // }
        // if (src == 2 && dst == 1)
        // { // case 3: move 1 disc from pole 2 to pole 1

        //     moves += "2->1\n";
        //     return moves;
        // }
        // if (src == 2 && dst == 3)
        // { // case 4: move 1 disc from pole 2 to pole 3

        //     moves += "2->3\n";
        //     return moves;
        // }
        // if (src == 3 && dst == 1)
        // { // case 5: move 1 disc from pole 3 to pole 1

        //     moves += "3->1\n";
        //     return moves;
        // }
        // if (src == 3 && dst == 2)
        // { // case 6: move 1 disc from pole 3 to pole 2

        //     moves += "3->2\n";
        //     return moves;
        // }
    }

    moves += get_moves(num_discs - 1, src, tmp, dst); // moves the "blocking stack to the temp"
    string biggest_move = to_string(src) + "->" + to_string(dst) + "\n";
    moves += biggest_move;
    moves += get_moves(num_discs - 1, tmp, dst, src); // moving the "blocking stack"located at temp on top of the now correctly positioned large disk
    _cache[num_discs][src][dst] = moves;
    _cache[num_discs-1].clear();
    return moves;
}

std::string Hanoi::lookup_moves(int num_discs, int src, int dst) const
{
    if (!_cache[num_discs][src][dst].empty())
    {
        return _cache[num_discs][src][dst];
    }
    return "";
}

std::string Hanoi::solve(int num_discs, int src, int dst, int tmp)
{
    string res = "# Below, 'A->B' means 'move the top disc on pole A to pole B'\n";
    res += get_moves(num_discs, src, dst, tmp);
    return res;
}

// int main(int argc, char const *argv[])
// {
//     Hanoi ToH;
//     cout << ToH.solve(3,1,3,2);

// }
