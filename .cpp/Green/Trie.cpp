// Student ID: 20527001
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include "Trie.h"
using namespace std;

Trie::Trie()
{
    _root = new Trie::Node();
}

void Trie::Node::insert(string s)
{
    Trie::Node *curr = this;
    if (s.empty())
    {
        if (next.size() == 0)
        {
            next.resize(1);
        }
        if (next[0] == nullptr)
        {
            next[0] = new Trie::Node();
        }
        return;
    }
    for (char c : s)
    {
        if (curr->next.size() < static_cast<size_t>(c + 1))
        {
            curr->next.resize(c + 1);
        }

        if (curr->next[int(c)] == nullptr)
        {
            curr->next[int(c)] = new Trie::Node();
        }
        curr = curr->next[int(c)];
    }
    if (curr->next.size() == 0)
    {
        curr->next.resize(1);
    }
    if (curr->next[0] == nullptr)
    {
        curr->next[0] = new Trie::Node();
    }
    return;
}

const Trie::Node *Trie::Node::traverse(string s) const
{
    const Trie::Node *curr = this;
    for (char c : s)
    {
        if (curr->next.size() >= static_cast<size_t>(c + 1))
        {
            if (curr->next[int(c)] == nullptr)
            {
                return nullptr;
            }
            curr = curr->next[int(c)];
        }
        else
        {
            return nullptr;
        }
    }

    return curr;
}

bool Trie::Node::lookup(string s) const
{
    const Trie::Node *curr = this->traverse(s);
    return (curr != nullptr && curr->next.at(0) != nullptr);
}
Trie::~Trie()
{
    delete _root;
}
size_t Trie::Node::get_completions(vector<string> &completions, size_t limit) const
{
    struct Continuation
    {
        const Trie::Node *node;
        string partial;
        Continuation(const Node *p, string s) : node(p), partial(s) {}
    };
    completions.clear();
    queue<Continuation> unprocessed_nodes;
    unprocessed_nodes.push(Continuation(this, ""));

    while (!unprocessed_nodes.empty() && completions.size() < limit)
    {
        Continuation cont = unprocessed_nodes.front();
        unprocessed_nodes.pop();

        for (size_t i = 0; i < cont.node->next.size(); i++)
        {
            if (cont.node->next[i] == nullptr)
                continue;
            if (i == 0)
            {
                completions.push_back(cont.partial);
                if (completions.size() >= limit)
                    break;
            }
            else
            {
                unprocessed_nodes.push(Continuation(cont.node->next[i], cont.partial + char(i)));
            }
        }
    }

    return completions.size();
}

size_t Trie::get_completions(string s, vector<string> &completions, size_t limit) const
{
    const Trie::Node *node = this->traverse(s);
    if (node != nullptr)
    {
        return node->get_completions(completions, limit);
    }
    return 0;
}

Trie::Node::~Node()
{
    for (auto nextNode : next)
    {
        if (nextNode != nullptr)
        {
            delete nextNode;
        }
    }
}

string Trie::to_string(size_t limit) const
{
    vector<string> completions;
    get_completions("", completions, limit);
    string result = "# Trie contents\n";
    for (size_t i = 0; i < completions.size(); i++)
    {
        result += completions[i] + "\n";
    }
    if (completions.size() == limit)
    {
        result += "...\n";
    }
    return result;
}
size_t Trie::trie_sort(vector<string> &vec) const
{
    vec.clear();
    get_completions("", vec, (size_t)-1);
    return vec.size();
}