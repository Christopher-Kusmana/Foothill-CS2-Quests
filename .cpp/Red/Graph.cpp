// Student ID: 20527001
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
#include "Graph.h"
using namespace std;

Graph &Graph::add_edge(int src, int tgt, float wt, bool replace)
{

    if (static_cast<int>(get_num_nodes()) <= max(src, tgt))
    {
        _nodes.resize(max(src, tgt) + 1);
    }
    if (src == tgt)
    {
        return *this;
    }

    for (auto &edge : _nodes[src])
    {
        if (edge.dst == tgt)
        {
            if (replace)
            {

                edge.wt = wt;
            }
            else
            {

                edge.wt += wt;
            }
            return *this;
        }
    }

    _nodes[src].emplace_back(Graph::Edge(tgt, wt));

    return *this;
}

float Graph::find_edge_weight(int src, int tgt) const
{
    if (src <= static_cast<int>(get_num_nodes()))
    {
        for (const auto &edge : _nodes[src])
        {
            if (edge.dst == tgt)
            {
                return edge.wt;
            }
        }
    }
    return Graph::FLOOR;
}
string Graph::to_string() const
{
    ostringstream oss;
    oss << "# Graph - " << get_num_nodes() << " nodes." << endl;
    oss << "# Edge lists:" << endl;
    for (size_t i = 0; i < _nodes.size(); i++)
    {
        if (_nodes[i].size() > 0)
        {
            oss << i << " : ";
        }
        for (size_t j = 0; j < _nodes[i].size(); j++)
        {
            oss << "(" << _nodes[i][j].dst << "," << _nodes[i][j].wt << ")";
            if (j + 1 != _nodes[i].size())
            {
                oss << " ";
            }
        }
        if (_nodes[i].size() > 0)
        {
            oss << endl;
        }
    }
    oss << "# End of Graph" << endl;
    return oss.str();
}
