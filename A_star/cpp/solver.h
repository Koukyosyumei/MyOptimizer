#pragma once
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "node.h"
using namespace std;

template <typename T>
struct Solver_AStar
{
    T start_node;
    T goal_node;
    T final_node;
    OpenList<T> openlist;
    ClosedList<T> closedlist;
    int num_visited_node = 0;

    Solver_AStar(T start_node, T goal_node)
    {
        this->start_node = start_node;
        this->goal_node = goal_node;

        openlist.goal_node = goal_node;
        openlist.insert(this->start_node);
    }

    bool solve()
    {
        bool issolved = false;
        T present_node;

        while (!openlist.isempty())
        {
            present_node = openlist.pop();
            if (present_node.isequal(this->goal_node))
            {
                issolved = true;
                break;
            }

            closedlist.insert(present_node);
            ++num_visited_node;

            vector<T> candidates = present_node.get_all_children();
            for (auto next_node : candidates)
            {
                if (!next_node.isnull && !closedlist.isclosed(next_node))
                    openlist.insert(next_node);
            }
        }

        final_node = present_node;
        return issolved;
    }
};