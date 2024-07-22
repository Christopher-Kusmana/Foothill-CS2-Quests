// Student ID: 20527001
#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <cfloat>
#include <list>
using namespace std;

// The graph is represented as a vector of nodes in which each node has
//  a vector of edges. Each edge is represented by a target node and the
//  weight of that edge
class Graph
{
public:
    struct Edge
    {
        int dst;
        float wt;
        Edge(int tgt = -1, float w = 0) : dst(tgt), wt(w) {}
        bool operator==(const Edge &that) const { return dst == that.dst && wt == that.wt; }
        bool operator!=(const Edge &that) const { return dst != that.dst && wt != that.wt; }
    };

protected:
    static double constexpr FLOOR = 1e-6;
    std::vector<std::vector<Edge>> _nodes;

public:
    size_t get_num_nodes() const { return _nodes.size(); }
    bool is_empty() const { return _nodes.empty(); }
    void clear() { _nodes.clear(); }
    std::string to_string() const;
    Graph &add_edge(int src, int tgt, float wt, bool replace = true);
    float find_edge_weight(int src, int tgt) const;

    friend class Gx;
    friend class Tests;
};

#endif