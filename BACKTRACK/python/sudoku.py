import copy


class Node_Sudoku:
    def __init__(self, pattern, board_size, cell_size, previous_node=None):
        self.pattern = pattern
        self.board_size = board_size
        self.cell_size = cell_size
        self.all_numbers = set([i for i in range(1, self.board_size + 1)])

        self.previous_node = previous_node

    def _culc_cell_idx(self, x, y):
        return (y // self.cell_size) * self.cell_size + (x // self.cell_size)

    def _remain_column(self, x, y):
        return self.all_numbers - set([self.pattern[i][x] for
                                       i in range(self.board_size)])

    def _remain_row(self, x, y):
        return self.all_numbers - set(self.pattern[y])

    def _remain_cell(self, x, y):
        cell_idx = self._culc_cell_idx(x, y)
        return self.all_numbers - set(self._get_cell_element(cell_idx))

    def _available_numbers(self, x, y):
        return self._remain_column(x, y) & self._remain_row(x, y) &\
            self._remain_cell(x, y)

    def _next(self, x, y, element):

        next_pattern = copy.deepcopy(self.pattern)
        next_pattern[y][x] = element
        return Node_Sudoku(next_pattern, self.board_size, self.cell_size,
                           previous_node=self)

    def _get_cell_element(self, cell_idx):
        cell_row_idx = cell_idx // self.cell_size
        cell_column_idx = cell_idx % self.cell_size
        cell_elements = []
        for i in range(cell_row_idx*self.cell_size,
                       (cell_row_idx+1)*self.cell_size):
            for j in range(cell_column_idx*self.cell_size,
                           (cell_column_idx+1)*self.cell_size):
                cell_elements.append(self.pattern[i][j])

        return cell_elements

    def _check_each_cell(self, cell_idx):
        cell_elements = self._get_cell_element(cell_idx)
        return set(cell_elements) == self.all_numbers

    def _check_each_column(self, column_idx):
        tmp_column_pattern = [self.pattern[i][column_idx] for
                              i in range(self.board_size)]
        return set(tmp_column_pattern) == self.all_numbers

    def _check_each_row(self, row_idx):
        return set(self.pattern[row_idx]) == self.all_numbers

    def _is_solved(self):
        for i in range(self.board_size):
            if not self._check_each_cell(i):
                return False
        for i in range(self.board_size):
            if not self._check_each_column(i):
                return False
        for i in range(self.board_size):
            if not self._check_each_row(i):
                return False

        return True

    def print(self):
        for i in range(self.board_size):
            print(self.pattern[i])


def backtrck_sudoku(current_node, blank_value=0):
    board_size = current_node.board_size
    for x in range(board_size):
        for y in range(board_size):
            if current_node.pattern[y][x] == blank_value:
                available_numbers = list(current_node._available_numbers(x, y))
                for an in available_numbers:
                    next_node = current_node._next(x, y, an)
                    if next_node._is_solved():
                        return next_node
                    else:
                        solution = backtrck_sudoku(
                            next_node, blank_value=blank_value)
                        if solution is not None:
                            return solution


if __name__ == "__main__":
    pattern = [[1, 2, 3, 0],
               [4, 0, 1, 2],
               [3, 4, 0, 1],
               [0, 0, 0, 0]]

    initial_node = Node_Sudoku(pattern, 4, 2)
    solution = backtrck_sudoku(initial_node)
    solution.print()
