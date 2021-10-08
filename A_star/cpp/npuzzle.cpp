#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "solver.h"
#include "utils.h"

const int w = 2;

int main()
{
    int n;
    cin >> n;
    cout << "dim of board is " << n << endl;

    vector<int> start_pattern(n * n);
    vector<int> goal_pattern(n * n);
    pair<int, int> start_blank;
    pair<int, int> goal_blank;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> start_pattern[i * n + j];
            if (start_pattern[i * n + j] == 0)
                start_blank = make_pair(i, j);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> goal_pattern[i * n + j];
            if (goal_pattern[i * n + j] == 0)
                goal_blank = make_pair(i, j);
        }
    }

    Node_N_Puzzle start_node = Node_N_Puzzle(n, w, 0, -1, "start", start_pattern, make_pair("", ""), start_blank);
    Node_N_Puzzle goal_node = Node_N_Puzzle(n, w, 0, -1, "goal", goal_pattern, make_pair("", ""), goal_blank);
    cout << "start_node is " << endl;
    start_node.print();
    cout << "goal_node is " << endl;
    goal_node.print();
    cout << endl;

    // Solver_AStar<Node_N_Puzzle> solver = Solver_AStar<Node_N_Puzzle>(start_node, goal_node);
    Solver_IDAStar<Node_N_Puzzle> solver = Solver_IDAStar<Node_N_Puzzle>(start_node, goal_node);
    clock_t start_time, end_time;
    bool issolved = solver.solve();
    end_time = clock();
    printf("time = %f[s]", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    cout << endl;
    cout << "num of visited nodes is " << solver.num_visited_node << endl;
    cout << "node per sec is " << solver.num_visited_node / ((double)(end_time - start_time) / CLOCKS_PER_SEC) << endl;

    if (issolved)
    {
        cout << "ths solution is " << endl;
        reverse_path_nqueen(solver.final_node, solver.closedlist);
    }
    else
    {
        cout << "we cannot find any solution" << endl;
    }
}