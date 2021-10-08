#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <map>
#include <string>
#include <queue>
using namespace std;

int directions[2] = {-1, 1};

vector<int> pattern_to_walking_state(int n, vector<int> pattern, int dim)
{
    vector<int> walking_state(n * n, 0);
    if (dim == 1) //vertical
    {
        for (int i = 0; i < n * n; ++i)
            if (pattern[i] != 0)
                walking_state[(i / n) * n + (pattern[i] - 1) / n] += 1;
    }
    else //horizontal
    {
        for (int i = 0; i < n * n; ++i)
            if (pattern[i] != 0)
                walking_state[(i % n) * n + (pattern[i] - 1) % n] += 1;
    }
    return walking_state;
}

string state_to_string(vector<int> state)
{
    string encoded_state = "";
    for (auto s : state)
        encoded_state += to_string(s) + " ";
    return encoded_state;
}

int get_position(int d, int c, int n)
{
    if (d == 1)
        return c;
    else
        return n + c;
}

pair<unordered_map<string, int>,
     unordered_map<string, vector<string>>>
generate_vertical_table(int n)
{
    vector<int> goal(n * n, 0);
    for (int i = 0; i < n; ++i)
        goal[i * n + i] = n;
    goal[n * n - 1] = n - 1;

    unordered_map<string, int> vertical_table;
    unordered_map<string, vector<string>> vertical_table_link;
    queue<tuple<vector<int>, int, int>> que;
    que.push(make_tuple(goal, 0, n - 1));

    tuple<vector<int>, int, int> info;
    vector<int> state;
    int cost, emp_row;
    string encoded_state;
    while (!que.empty())
    {
        info = que.front();
        que.pop();
        state = get<0>(info);
        cost = get<1>(info);
        emp_row = get<2>(info);

        encoded_state = state_to_string(state);
        if (vertical_table.find(encoded_state) != vertical_table.end())
            continue;
        vertical_table[encoded_state] = cost;

        for (auto d : directions)
        {
            if ((0 <= emp_row + d) && (emp_row + d < n))
            {
                for (int c = 0; c < n; ++c)
                {
                    if (state[n * (emp_row + d) + c] > 0)
                    {
                        vector<int> next_state;
                        copy(state.begin(), state.end(), back_inserter(next_state));
                        next_state[n * (emp_row + d) + c] -= 1;
                        next_state[n * emp_row + c] += 1;
                        que.push(make_tuple(next_state, cost + 1, emp_row + d));
                        string next_state_string = state_to_string(next_state);
                        if (vertical_table_link.find(encoded_state) == vertical_table_link.end())
                            vertical_table_link[encoded_state] = vector<string>(2 * n, "");
                        vertical_table_link[encoded_state][get_position(d, c, n)] = next_state_string;
                        // vertical_table_link[next_state_string][get_position(-d, c)] = encoded_state;
                    }
                }
            }
        }
    }

    cout << "n = " << n << " size of vertical table is " << vertical_table.size() << endl;
    cout << "n = " << n << " size of vertical table link is " << vertical_table_link.size() << endl;

    return make_pair(vertical_table, vertical_table_link);
}

pair<unordered_map<string, int>,
     unordered_map<string, vector<string>>>
generate_horizontal_table(int n)
{
    vector<int> goal(n * n, 0);
    for (int i = 0; i < n; ++i)
        goal[i * n + i] = n;
    goal[n * n - 1] = n - 1;

    unordered_map<string, int> horizontal_table;
    unordered_map<string, vector<string>> horizontal_table_link;
    queue<tuple<vector<int>, int, int>> que;
    que.push(make_tuple(goal, 0, n - 1));

    tuple<vector<int>, int, int> info;
    vector<int> state;
    int cost, emp_col;
    string encoded_state;
    while (!que.empty())
    {
        info = que.front();
        que.pop();
        state = get<0>(info);
        cost = get<1>(info);
        emp_col = get<2>(info);

        encoded_state = state_to_string(state);
        if (horizontal_table.find(encoded_state) != horizontal_table.end())
            continue;
        horizontal_table[encoded_state] = cost;

        for (auto d : directions)
        {
            if ((0 <= emp_col + d) && (emp_col + d < n))
            {
                for (int c = 0; c < n; ++c)
                {
                    if (state[c * n + emp_col + d] > 0)
                    {
                        vector<int> next_state;
                        copy(state.begin(), state.end(), back_inserter(next_state));
                        next_state[c * n + emp_col + d] -= 1;
                        next_state[c * n + emp_col] += 1;
                        que.push(make_tuple(next_state, cost + 1, emp_col + d));
                        string next_state_string = state_to_string(next_state);
                        if (horizontal_table_link.find(encoded_state) == horizontal_table_link.end())
                            horizontal_table_link[encoded_state] = vector<string>(2 * n, "");
                        horizontal_table_link[encoded_state][get_position(d, c, n)] = next_state_string;
                        // if (encoded_state == "2 1 0 1 1 0 0 1 2")
                        //    cout << "found "
                        // horizontal_table_link[next_state_string][get_position(-d, c)] = encoded_state;
                    }
                }
            }
        }
    }

    cout << "n = " << n << " size of horizontal table is " << horizontal_table.size() << endl;
    cout << "n = " << n << " size of horizontal table link is " << horizontal_table_link.size() << endl;
    return make_pair(horizontal_table, horizontal_table_link);
}