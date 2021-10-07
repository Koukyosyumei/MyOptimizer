#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "solver.h"
#include "utils.h"

const int w = 1;

int main()
{
    int n;
    cin >> n;
    cout << "dim of board is " << n << endl;

    vector<vector<int>> start_pattern(n, vector<int>(n));
    vector<vector<int>> goal_pattern(n, vector<int>(n));
    pair<int, int> start_blank;
    pair<int, int> goal_blank;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> start_pattern[i][j];
            if (start_pattern[i][j] == 0)
                start_blank = make_pair(i, j);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> goal_pattern[i][j];
            if (goal_pattern[i][j] == 0)
                goal_blank = make_pair(i, j);
        }
    }

    Node_N_Puzzle start_node = Node_N_Puzzle(n, w, 0, "start", start_pattern, start_blank);
    Node_N_Puzzle goal_node = Node_N_Puzzle(n, w, 0, "goal", goal_pattern, goal_blank);
    cout << "start_node is " << endl;
    start_node.print();
    cout << "goal_node is " << endl;
    goal_node.print();
    cout << endl;

    Solver_AStar<Node_N_Puzzle> solver = Solver_AStar<Node_N_Puzzle>(start_node, goal_node);
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