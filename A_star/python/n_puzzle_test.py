from n_puzzle import Game_N_Puzzle, Node_N_Puzzle

if __name__ == '__main__':

    startloc = [[1, 2, 3], [8, 0, 5], [7, 4, 6]]
    goalloc = [[1, 6, 2], [8, 4, 3], [0, 5, 7]]

    # Define start and end node
    start = Node_N_Puzzle(startloc, 0, weight=1)
    goal = Node_N_Puzzle(goalloc, 0, 'goal')

    # Initilaize Game
    game = Game_N_Puzzle(start, goal)

    # Solve Game
    game.solve()

    # print the path
    game.print_path()
