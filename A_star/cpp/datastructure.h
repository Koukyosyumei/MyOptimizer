#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <cmath>
using namespace std;

template <typename T>
struct OpenList
{
    priority_queue<int, vector<int>, greater<int>> indices;
    unordered_map<int, vector<T>> nodes;
    T goal_node;

    bool isempty()
    {
        return indices.empty(); // O(1)
    }

    void insert(T node)
    {
        int idx = node.get_evaluation_value(this->goal_node);
        // O(1)
        if (nodes.find(idx) != nodes.end())
        {
            nodes[idx].push_back(node); // O(1)
        }
        else
        {
            indices.push(idx); // O(1)
            nodes[idx] = vector<T>();
            nodes[idx].push_back(node);
        }
    }

    int get_idx_within_nodes(vector<T> node_vector, T node)
    {
        int idx = 0;
        for (auto temp_node : node_vector)
        {
            if (node.isequal(temp_node))
                break;
            ++idx;
        }
        return idx;
    }

    void remove(T node)
    {
        int idx = node.get_evaluation_value(this->goal_node);
        nodes[idx].erase(nodes[idx].begin() + get_idx_within_nodes(nodes[idx], node));
        if (nodes[idx].empty())
        {
            nodes.erase(idx);
            indices.pop();
        }
    }

    T front()
    {
        return nodes[indices.top()].front();
    }

    T pop()
    {
        int idx = indices.top();
        T poped_node = nodes[idx].back();
        nodes[idx].pop_back();
        if (nodes[idx].empty())
        {
            nodes.erase(idx);
            indices.pop();
        }
        return poped_node;
    }
};

template <typename T>
struct ClosedList
{
    unordered_map<long, T> hash_table;

    void insert(T node)
    {
        long idx = node.get_hash_value();
        hash_table.insert({idx, node});
    }

    bool isclosed(T node)
    {
        long idx = node.get_hash_value();
        return hash_table.find(idx) != hash_table.end();
    }
};