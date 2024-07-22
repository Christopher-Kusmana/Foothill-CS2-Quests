// Student ID: 20527001
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <sstream>
using namespace std;
#ifndef TRIE_H
#define TRIE_H

class Trie
{
private:
    struct Node
    {
        vector<Trie::Node*> next;
        ~Node();
        void insert(string s);
        const Node *traverse(string s) const;
        bool lookup(string s) const;    
        size_t get_completions(vector<string> &completions, size_t limit) const;
    }; 

    
    Trie::Node *_root;
    // Private Trie:: helper. Return interior node traversing from root
    const Node *traverse(string s) const { return _root->traverse(s); }

public:
    Trie();
    ~Trie();
    void insert(string s) { _root->insert(s); }
    bool lookup(string s) const { return _root->lookup(s); }
    size_t get_completions(string s, vector<string> &completions, size_t limit) const;
    size_t trie_sort(vector<string> &vec) const;
    string to_string(size_t n) const;
    ostream &operator<<(ostream &os) { return os << to_string(100); }
    friend class Tests;
};

#endif
