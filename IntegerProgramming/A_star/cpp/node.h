#pragma once
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <functional>
#include <unordered_map>
#include "datastructure.h"
#include "walking_distance.h"
using namespace std;

#define heuristic_function "wd" //wd or md

hash<string> hasher;

map<string, pair<int, int>>
    movedict{
        {"left", make_pair(0, -1)},
        {"right", make_pair(0, 1)},
        {"up", make_pair(-1, 0)},
        {"down", make_pair(1, 0)}};

unordered_map<int, pair<unordered_map<string, int>,
                        unordered_map<string, vector<string>>>>
    n_to_tables{
        {3, generate_walking_distance_table(3)},
        {4, generate_walking_distance_table(4)}};

string get_state_string(vector<int> state)
{
    stringstream ss;
    copy(state.begin(), state.end(), ostream_iterator<int>(ss, " "));
    string state_string = ss.str();
    state_string = state_string.substr(0, state_string.length() - 1);
    return state_string;
}

struct Node_N_Puzzle
{
    int n, h, g, f, w;
    string prev_move;
    pair<string, string> encoded_pattern;
    vector<int> pattern;
    pair<int, int> blank;
    bool isnull;
    string state_string;

    Node_N_Puzzle() { isnull = true; }
    Node_N_Puzzle(int n, int w, int g, int h, string prev_move,
                  vector<int> pattern, pair<string, string> encoded_pattern, pair<int, int> blank)
    {
        this->n = n;
        this->w = w;
        this->g = g;
        this->prev_move = prev_move;
        this->pattern = pattern;
        if (encoded_pattern.first == "" || encoded_pattern.second == "")
            this->encoded_pattern = make_pair(state_to_string(pattern_to_walking_state(n, pattern, 1)),
                                              state_to_string(pattern_to_walking_state(n, pattern, 0)));
        else
            this->encoded_pattern = encoded_pattern;
        this->blank = blank;

        this->h = h;
        this->f = -1;
        this->isnull = false;
        this->state_string = get_state_string(this->pattern);
    }

    int get_linear_conflict()
    {
        int conflict_value = 0;
        for (int i = 0; i < n * n; ++i)
        {
            if (this->pattern[i] == 0)
                continue;
            if (this->pattern[i] / n == i / n)
                for (int j = i + 1; j < ((i / n) + 1) * n; ++j)
                    if ((this->pattern[j] > 0) &&
                        (this->pattern[j] / n == i / n) &&
                        (this->pattern[j] < this->pattern[i]))
                        conflict_value += 2;
            if (this->pattern[i] % n == i % n)
                for (int j = i + n; j < n * n; j += n)
                    if ((this->pattern[j] > 0) &&
                        (this->pattern[j] % n == i % n) &&
                        (this->pattern[j] < this->pattern[i]))
                        conflict_value += 2;
        }

        return conflict_value;
    }

    int get_misplaced_tiles(Node_N_Puzzle goal)
    {
        int distance = 0;
        for (int i = 0; i < n * n; ++i)
            if (pattern[i] != goal.pattern[i])
                ++distance;

        if (blank == goal.blank)
            --distance;

        return distance;
    }

    int get_manhatten_distance(Node_N_Puzzle goal)
    {
        // TODO: どんなゴール状態にも対応できるようにする
        int distance = 0;
        if (this->h < 0)
        {

            for (int i = 0; i < n * n; ++i)
                if (pattern[i] != 0)
                    distance += abs((i / this->n) - (pattern[i] / this->n)) + abs((i % this->n) - (pattern[i] % this->n));
        }
        else
        {
            distance = this->h;
        }
        return distance;
    }

    int get_walking_distance()
    {
        int distance;
        if (this->h < 0)
            distance = n_to_tables[n].first[encoded_pattern.first] +
                       n_to_tables[n].first[encoded_pattern.second];
        else
            distance = this->h;

        // distance += get_linear_conflict();
        return distance;
    }

    int get_evaluation_value(Node_N_Puzzle goal)
    {
        if (heuristic_function == "wd")
            this->h = get_walking_distance();
        else if (heuristic_function == "md")
            this->h = get_manhatten_distance(goal);
        this->f = this->g + this->w * this->h;
        return this->f;
    }

    Node_N_Puzzle get_child_node(string move)
    {
        int y = movedict[move].first;
        int x = movedict[move].second;

        if ((0 > this->blank.first + y) || (this->blank.first + y >= n))
            return Node_N_Puzzle();
        if ((0 > this->blank.second + x) || (this->blank.second + x >= n))
            return Node_N_Puzzle();

        vector<int> child_pattern;
        copy(this->pattern.begin(), this->pattern.end(), back_inserter(child_pattern));
        int blank_idx = this->blank.first * n + this->blank.second;
        int target_idx = (this->blank.first + y) * n + this->blank.second + x;

        child_pattern[blank_idx] = child_pattern[target_idx];
        child_pattern[target_idx] = 0;

        int next_h = -1;
        if (heuristic_function == "md")
            next_h = this->h -
                     (abs((target_idx / this->n) - (this->pattern[target_idx] / this->n)) +
                      abs((target_idx % this->n) - (this->pattern[target_idx] % this->n))) +
                     (abs((blank_idx / this->n) - (this->pattern[target_idx] / this->n)) +
                      abs((blank_idx % this->n) - (this->pattern[target_idx] % this->n)));

        string encoded_child_pattern_vertical = "";
        string encoded_child_pattern_horizontal = "";
        if (heuristic_function == "wd")
        {
            if (this->encoded_pattern.first == "")
                this->encoded_pattern.first = state_to_string(pattern_to_walking_state(n, this->pattern, 1));
            if (this->encoded_pattern.second == "")
                this->encoded_pattern.second = state_to_string(pattern_to_walking_state(n, this->pattern, 0));
            if (y == 0)
                encoded_child_pattern_vertical = encoded_pattern.first;
            else
                encoded_child_pattern_vertical = n_to_tables[n].second[this->encoded_pattern.first][get_position(y, (child_pattern[blank_idx] - 1) / this->n, n)];
            if (x == 0)
                encoded_child_pattern_horizontal = encoded_pattern.second;
            else
                encoded_child_pattern_horizontal = n_to_tables[n].second[this->encoded_pattern.second][get_position(x, (child_pattern[blank_idx] - 1) % this->n, n)];
        }

        return Node_N_Puzzle(this->n, this->w, this->g + 1, next_h, move, child_pattern,
                             make_pair(encoded_child_pattern_vertical, encoded_child_pattern_horizontal),
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
        return equal(this->pattern.begin(), this->pattern.end(), node.pattern.begin());
    }

    void print()
    {
        for (int i = 0; i < this->n; ++i)
        {
            for (int j = 0; j < this->n; ++j)
                cout << this->pattern[i * n + j] << " ";
            cout << endl;
        }
    }
};