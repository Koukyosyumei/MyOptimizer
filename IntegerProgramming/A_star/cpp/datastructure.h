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

    void initialize(T g_node)
    {
        indices = priority_queue<int, vector<int>, greater<int>>();
        nodes = unordered_map<int, vector<T>>();
        goal_node = g_node;
    }

    bool isempty()
    {
        return indices.empty(); // O(1)
    }

    void insert(T node)
    {
        int idx;
        if (node.f < 0)
            idx = node.get_evaluation_value(this->goal_node);
        else
            idx = node.f;

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
    unordered_map<string, T> hash_table;

    void insert(T node)
    {
        hash_table.insert({node.state_string, node});
    }

    bool isclosed(T node)
    {
        return hash_table.find(node.state_string) != hash_table.end();
    }

    void initialize()
    {
        hash_table = unordered_map<string, T>();
    }
};