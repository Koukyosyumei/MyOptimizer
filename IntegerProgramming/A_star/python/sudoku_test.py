from sudoku import Game_Sudoku, Node_Sudoku

if __name__ == '__main__':
    """
    pattern = [[0, 0, 6, 3, 2, 0, 0, 0, 0],
               [0, 4, 0, 0, 0, 9, 0, 0, 0],
               [1, 0, 0, 0, 5, 7, 2, 0, 0],
               [9, 0, 0, 5, 0, 0, 1, 7, 0],
               [3, 0, 7, 0, 0, 0, 9, 0, 4],
               [0, 1, 2, 0, 0, 8, 0, 0, 5],
               [0, 0, 5, 8, 1, 0, 0, 0, 6],
               [0, 0, 0, 4, 0, 0, 0, 9, 0],
               [0, 0, 0, 0, 7, 6, 5, 0, 0]]
    """
    pattern = [[1, 2, 3, 0],
               [4, 0, 1, 2],
               [3, 4, 0, 1],
               [0, 0, 0, 0]]

    start = Node_Sudoku(pattern, 0, 4, 2, weight=3)

    game = Game_Sudoku(start, None)
    solved, node_answer = game.solve()
    if solved:
        node_answer.print()
    else:
        print("no solution")
