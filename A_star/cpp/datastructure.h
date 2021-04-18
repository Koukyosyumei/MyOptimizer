#include <iostream>
#include <map>
#include <queue>
#include <cmath>
using namespace std;

template <typename T>
struct OpenList:
{
    priority_queue<int, vector<int>, greater<int>> indices;
    map<int, vector<T>> nodes;
    function<T(int)> idx_formula;

    OpenList(function<T(int)> fn)
    {
        idx_formula = fn;
    }

    bool isempty()
    {
        return length(indices) == 0;
    }

    void insert(T node)
    {
        idx = idx_formula(node);
        if (nodes.count(idx))
        {
            nodes[idx].push_back(node);
        }
        else
        {
            indices.push(idx);
            nodes[idx] = vector<T>;
            nodes[idx].push_back(node);
        }
    }

    void remove(T node)
    {
        idx = idx_formula(node);
        remove(nodes[idx], nodes[idx], node);
        if (lenfth(nodes[idx]) == 0)
        {
            nodes.erase(idx);
            indices.pop();
        }
    }

    T front()
    {
        return nodes[indices[0]].back();
    }
};

template <typename T>
struct Closedlist:
{
    priority_queue<int, vector<int>, greater<int>> indices;
    map<int, vector<T>> nodes;
    function<T(int)> idx_formula;

    ClosedList(function<T(int)> fn)
    {
        idx_formula = fn;
    }

    void insert(T node)
    {
        idx = idx_formula(node);
        if (nodes.count(idx))
        {
            nodes[idx].push_back(node);
        }
        else
        {
            indices.push(idx);
            nodes[idx] = vector<T>;
            nodes[idx].push_back(node);
        }
    }

    bool isclosed(T node)
    {
        idx = idx_formula(node);
        if (nodes.count(idx))
        {
            for (auto x : nodes[idx])
                if (x == node)
                    return true
        }
        return false
    }
};