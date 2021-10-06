#pragma once
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "datastructure.h"
using namespace std;

#define mod 19997

map<string, pair<int, int>> movedict{
    {"left", make_pair(0, -1)},
    {"right", make_pair(0, 1)},
    {"up", make_pair(-1, 0)},
    {"down", make_pair(1, 0)}};

struct Node_N_Puzzle
{
    int n, h, g, w;
    string prev_move;
    vector<vector<int>> pattern;
    pair<int, int> blank;
    bool isnull;

    Node_N_Puzzle() { isnull = true; }
    Node_N_Puzzle(int n, int w, int g, string prev_move,
                  vector<vector<int>> pattern, pair<int, int> blank)
    {
        this->n = n;
        this->w = w;
        this->g = g;
        this->prev_move = prev_move;
        this->pattern = pattern;
        this->blank = blank;

        this->h = 0;
        this->isnull = false;
    }

    int get_hash_value()
    {
        int hash_value = 0;
        int hash_a = 63689;
        int hash_b = 378551;
        for (int i = 0; i < this->n; ++i)
        {
            for (int j = 0; j < this->n; ++j)
            {
                hash_value = hash_value * hash_a + this->pattern[i][j];
                hash_a = hash_a * hash_b;
            }
        }
        return hash_value;
    }

    int get_manhatten_distance(Node_N_Puzzle goal)
    {
        int distance = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (pattern[i][j] != goal.pattern[i][j])
                    ++distance;
            }
        }

        if (blank == goal.blank)
            --distance;

        return distance;
    }

    int get_evaluation_value(Node_N_Puzzle goal)
    {
        this->h = get_manhatten_distance(goal);
        return this->g + this->w * this->h;
    }

    Node_N_Puzzle get_child_node(string move)
    {
        int y = movedict[move].first;
        int x = movedict[move].second;

        if ((0 > this->blank.first + y) || (this->blank.first + y >= n))
            return Node_N_Puzzle();
        if ((0 > this->blank.second + x) || (this->blank.second + x >= n))
            return Node_N_Puzzle();

        vector<vector<int>> child_pattern;
        copy(this->pattern.begin(), this->pattern.end(), back_inserter(child_pattern));
        child_pattern[this->blank.first][this->blank.second] = child_pattern[this->blank.first + y][this->blank.second + x];
        child_pattern[this->blank.first + y][this->blank.second + x] = 0;
        return Node_N_Puzzle(this->n, this->w, this->g + 1, move, child_pattern,
                             make_pair(this->blank.first + y, this->blank.second + x));
    }

    vector<Node_N_Puzzle> get_all_children()
    {
        vector<Node_N_Puzzle> children;
        children.push_back(get_child_node("right"));
        children.push_back(get_child_node("left"));
        children.push_back(get_child_node("up"));
        children.push_back(get_child_node("down"));
        return children;
    }

    bool isequal(Node_N_Puzzle node)
    {
        bool flag = true;
        for (int i = 0; i < this->n; ++i)
        {
            for (int j = 0; j < this->n; ++j)
            {
                if (this->pattern[i][j] != node.pattern[i][j])
                {
                    flag = false;
                    return flag;
                }
            }
        }
        return flag;
    }

    void print()
    {
        for (int i = 0; i < this->n; ++i)
        {
            for (int j = 0; j < this->n; ++j)
            {
                cout << this->pattern[i][j] << " ";
            }
            cout << endl;
        }
    }
};