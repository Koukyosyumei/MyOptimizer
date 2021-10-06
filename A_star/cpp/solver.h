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
            present_node = openlist.front();
            present_node.print();
            cout << endl;
            if (present_node.isequal(this->goal_node))
            {
                issolved = true;
                break;
            }

            openlist.remove(present_node);
            closedlist.insert(present_node);

            vector<T> candidates = present_node.get_all_children();
            for (auto next_node : candidates)
            {
                if (!next_node.isnull)
                    openlist.insert(next_node);
            }
        }

        final_node = present_node;
        return issolved;
    }
};