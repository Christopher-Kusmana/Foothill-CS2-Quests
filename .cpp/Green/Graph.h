// Student ID: 20527001
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <sstream>
using namespace std;
#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
protected:
    struct Edge
    {
        int _dst;
        std::string _tag;
        Edge(int dst = -1, std::string tag = "") : _dst(dst), _tag(tag) {}
    };
    std::vector<std::vector<Edge>> _nodes;
    // Suggested private helpers. Not tested.
    void add_edge(int src, int dst, std::string tag);
    std::string to_string() const;

public:
    void make_silly_snake();
    void make_mr_sticky();
    void make_driftin_dragonfly();
    void make_slinky_star();
    void make_kathy_da_grate();
    void make_dodos_in_space();
    void make_purty_pitcher();
    friend class Tests; // Don't remove this line.
};

#endif