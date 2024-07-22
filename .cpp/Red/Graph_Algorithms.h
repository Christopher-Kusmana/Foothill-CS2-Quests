// Student ID: 20527001
#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <limits>
#include <string>
#include <sstream>
#include <cstddef>
#include <queue>
#include <ostream>
#include <cmath>
#include <cfloat>
#include <list>
#include "Graph.h"
using namespace std;

class Gx
{
private:
    struct NW
    {
        int node, pred;
        float weight;
        NW(int n, int m, float wt) : node(n), pred(m), weight(wt) {}
        bool operator<(const NW &that) const { return this->weight > that.weight; }
        bool operator>(const NW &that) const { return this->weight > that.weight; }
    };
    static bool _is_cyclic(const Graph &g, size_t node, std::vector<bool> seen, std::vector<bool> &cycle_free)
    {
        if (seen[node] == true)
        {
            return true;
        }
        if (!cycle_free[node])
        {
            return true;
        }
        seen[node] = true;
        for (size_t i = 0; i < g._nodes[node].size(); i++)
        {
            if (_is_cyclic(g, g._nodes[node][i].dst, seen, cycle_free))
            {
                cycle_free[g._nodes[node][i].dst] = false;
                return true;
            }
        }
        return false;
    }
    static void _prune_helper(Graph &g, int src, vector<bool> &seen)
    {
        seen[src] = true;
        for (size_t i = 0; i < g._nodes[src].size(); i++)
        {
            if (g._nodes[src][i].dst < static_cast<int>(seen.size()) && !seen[g._nodes[src][i].dst])
            {
                _prune_helper(g, g._nodes[src][i].dst, seen);
            }
        }
    }

    static float _get_capacity_of_this_path(const Graph &g, const vector<int> &path)
    {
        float bottleneck = std::numeric_limits<float>::max();

        for (auto it = path.begin(); it != path.end() - 1; ++it)
        {
            int u = *it;
            int v = *(it + 1);
            float wt = g.find_edge_weight(u, v);

            if (wt < bottleneck)
            {
                bottleneck = wt;
            }
        }

        return bottleneck;
    }

public:
    static float _get_max_capacity_path(const Graph &g, int src, int dst, std::vector<int> &path)
    {
        path.clear();
        queue<int> q;
        q.push(src);

        vector<bool> visited(g.get_num_nodes(), false);
        vector<int> parent(g.get_num_nodes(), -1);

        visited[src] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (const auto &edge : g._nodes[u])
            {
                int v = edge.dst;

                if (!visited[v] && edge.wt > 0)
                {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        if (!visited[dst])
        {

            return 0;
        }
        int u = dst;
        path.push_back(u);

        while (parent[u] != -1)
        {
            path.push_back(parent[u]);
            u = parent[u];
        }

        std::reverse(path.begin(), path.end());

        float bottleneck = _get_capacity_of_this_path(g, path);

        return bottleneck;
    }

    static bool is_cyclic(const Graph &g)
    {
        vector<bool> cycle_free(g.get_num_nodes(), true);
        for (size_t node = 0; node < g.get_num_nodes(); ++node)
        {
            if (_is_cyclic(g, node, std::vector<bool>(g.get_num_nodes(), false), cycle_free))
            {
                return true;
            }
        }
        return false;
    }

    static bool prune_unreachables(Graph &g, int src)
    {
        if (static_cast<int>(g.get_num_nodes()) < src || src < 0)
        {
            return false;
        }
        vector<bool> reachable(g.get_num_nodes(), false);
        _prune_helper(g, src, reachable);
        for (size_t i = 0; i < reachable.size(); i++)
        {
            if (reachable[i] == false)
            {
                g._nodes[i].clear();
            }
        }
        return true;
    }
    static size_t get_shortest_unweighted_path(Graph &g, int src, int dst, std::vector<int> &path)
    {
        if (src < 0 || src > static_cast<int>(g.get_num_nodes()) ||
            dst < 0 || dst > static_cast<int>(g.get_num_nodes()))
        {
            return std::string::npos;
        }
        path.clear();
        if (src == dst)
        {
            path.push_back(src);
            return 1;
        }
        std::queue<int> q;
        std::vector<int> prev(g.get_num_nodes(), -1);
        std::vector<bool> visited(g.get_num_nodes(), false);
        q.push(src);
        visited[src] = true;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (const auto &edge : g._nodes[curr])
            {
                int next = edge.dst;
                if (!visited[next])
                {
                    visited[next] = true;
                    prev[next] = curr;
                    q.push(next);
                    if (next == dst)
                    {
                        int p = dst;
                        while (p != -1)
                        {
                            path.push_back(p);
                            p = prev[p];
                        }

                        std::reverse(path.begin(), path.end());
                        return path.size();
                    }
                }
            }
        }
        return std::string::npos;
    }
    static size_t get_shortest_weighted_path(const Graph &g, int src, int dst, std::vector<int> &path)
    {
        if (src < 0 || src > static_cast<int>(g.get_num_nodes()) ||
            dst < 0 || dst > static_cast<int>(g.get_num_nodes()))
        {
            return std::string::npos;
        }

        path.clear();
        if (src == dst)
        {
            path.push_back(src);
            return 1;
        }

        std::vector<float> dist(g.get_num_nodes(), std::numeric_limits<float>::max());
        std::vector<int> prev(g.get_num_nodes(), -1);
        dist[src] = 0;

        std::priority_queue<NW, std::vector<NW>, std::greater<NW>> pq;
        pq.push(NW(src, -1, 0));

        while (!pq.empty())
        {
            NW curr = pq.top();
            pq.pop();
            if (curr.node == dst)
            {
                int p = dst;
                while (p != -1)
                {
                    path.push_back(p);
                    p = prev[p];
                }
                std::reverse(path.begin(), path.end());
                return path.size();
            }
            if (dist[curr.node] < curr.weight)
                continue;
            for (const auto &edge : g._nodes[curr.node])
            {
                int next = edge.dst;
                float weight = edge.wt;
                if (dist[curr.node] + weight < dist[next])
                {
                    dist[next] = dist[curr.node] + weight;
                    prev[next] = curr.node;
                    pq.push(NW(next, curr.node, dist[next]));
                }
            }
        }
        return std::string::npos;
    }
    static float get_max_flow(const Graph &g, int src, int dst)
    {
        Graph residual = g;
        float max_flow = 0;

        vector<int> path;
        float bottleneck = _get_max_capacity_path(residual, src, dst, path);
        while (bottleneck > 0)
        {

            max_flow += bottleneck;

            for (auto it = path.begin(); it != path.end() - 1; ++it)
            {
                int u = *it;
                int v = *(it + 1);
                residual.add_edge(u, v, -bottleneck, false);
                residual.add_edge(v, u, bottleneck, false);
            }

            bottleneck = _get_max_capacity_path(residual, src, dst, path);
        }

        return max_flow;
    }

    friend class Tests;
};

#endif