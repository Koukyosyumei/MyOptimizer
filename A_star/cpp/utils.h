#pragma once
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include "node.h"

void reverse_path_nqueen(Node_N_Puzzle final_node, ClosedList<Node_N_Puzzle> closedlist)
{
    map<string, string> move_reverse = {{"up", "down"},
                                        {"down", "up"},
                                        {"left", "right"},
                                        {"right", "left"}};

    Node_N_Puzzle present_node = final_node;
    while (present_node.prev_move != "start")
    {
        // present_node.print();
        cout << present_node.prev_move << " ";
        if (present_node.prev_move == "up")
            present_node = present_node.get_child_node("down");
        else if (present_node.prev_move == "down")
            present_node = present_node.get_child_node("up");
        else if (present_node.prev_move == "left")
            present_node = present_node.get_child_node("right");
        else if (present_node.prev_move == "right")
            present_node = present_node.get_child_node("left");

        present_node = closedlist.hash_table[present_node.get_hash_value()];
        /*
        for (auto temp_node : closedlist.hash_table[present_node.get_hash_value()])
        {
            if (present_node.isequal(temp_node))
                present_node = temp_node;
        }
        */
    }
    // present_node.print();
    cout << endl;
}