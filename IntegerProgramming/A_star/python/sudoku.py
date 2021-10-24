import copy

from core import Game, Node


class Node_Sudoku(Node):
    def __init__(self, pattern, gfunc, board_size, cell_size, weight=1):
        self.pattern = pattern
        self.gfunc = gfunc
        self.weight = weight
        self.BOARD_SIZE = board_size
        self.CELL_SIZE = cell_size
        self._one_to_nine = set(list(range(1, self.BOARD_SIZE+1)))
        assert len(pattern) == self.BOARD_SIZE
        assert len(pattern[0]) == self.BOARD_SIZE

    def __eq__(self, other):
        if other is None:
            return False

        if not isinstance(other, type(self)):
            raise TypeError(f"other should be {type(self)}")

        self.pattern == other.pattern

    def __getitem__(self, key):
        if not isinstance(key, tuple):
            raise TypeError("Key should be tuple")

        if len(key) != 2:
            raise KeyError(f"length of key must be 2, not {len(key)}")

        return self.pattern[key[0]][key[1]]

    def _culc_cell_idx(self, x, y):
        return (y // self.CELL_SIZE) * self.CELL_SIZE + (x // self.CELL_SIZE)

    def _remain_column(self, x, y):
        return self._one_to_nine - set([self.pattern[i][x] for
                                        i in range(self.BOARD_SIZE)])

    def _remain_row(self, x, y):
        return self._one_to_nine - set(self.pattern[y])

    def _remain_cell(self, x, y):
        cell_idx = self._culc_cell_idx(x, y)
        return self._one_to_nine - set(self._get_cell_element(cell_idx))

    def _remain_value(self, x, y):
        return self._remain_column(x, y) & self._remain_row(x, y) &\
            self._remain_column(x, y)

    def calc_hfunc(self, goal):
        self.hfunc = 0
        for x in range(self.BOARD_SIZE):
            for y in range(self.BOARD_SIZE):
                if self.pattern[y][x] == 0:
                    self.hfunc += len(list(self._remain_value(x, y)))
        self.ffunc = self.gfunc + self.weight*self.hfunc

        return self.hfunc, self.gfunc, self.ffunc

    def _replace(self, x, y, element):
        tmp_column_pattern = [self.pattern[i][x] for
                              i in range(self.BOARD_SIZE)]
        if element in tmp_column_pattern:
            return None

        if element in self.pattern[y]:
            return None

        cell_idx = self._culc_cell_idx(x, y)
        if element in self._get_cell_element(cell_idx):
            return None

        next_pattern = copy.deepcopy(self.pattern)
        next_pattern[y][x] = element
        return Node_Sudoku(next_pattern, self.gfunc+1,
                           self.BOARD_SIZE, self.CELL_SIZE, weight=self.weight)

    def moveall(self, game):
        next_nodes = []
        for x in range(self.BOARD_SIZE):
            for y in range(self.BOARD_SIZE):
                if self.pattern[y][x] == 0:
                    for i in range(1, self.BOARD_SIZE+1):
                        next_node = self._replace(x, y, i)
                        next_node = None if next_node is None or\
                            game.closedlist.isclosed(
                                next_node) else next_node
                        game.openlist.insert(next_node)
                        next_nodes.append(next_node)

        game.closedlist.insert(self)
        return next_nodes

    def print(self):
        for i in range(self.BOARD_SIZE):
            print(self.pattern[i])

    def _get_cell_element(self, cell_idx):
        cell_row_idx = cell_idx // self.CELL_SIZE
        cell_column_idx = cell_idx % self.CELL_SIZE
        cell_elements = []
        for i in range(cell_row_idx*self.CELL_SIZE,
                       (cell_row_idx+1)*self.CELL_SIZE):
            for j in range(cell_column_idx*self.CELL_SIZE,
                           (cell_column_idx+1)*self.CELL_SIZE):
                cell_elements.append(self.pattern[i][j])

        return cell_elements

    def _check_each_cell(self, cell_idx):
        cell_elements = self._get_cell_element(cell_idx)
        return set(cell_elements) == self._one_to_nine

    def _check_each_column(self, column_idx):
        tmp_column_pattern = [self.pattern[i][column_idx] for
                              i in range(self.BOARD_SIZE)]
        return set(tmp_column_pattern) == self._one_to_nine

    def _check_each_row(self, row_idx):
        return set(self.pattern[row_idx]) == self._one_to_nine

    def _is_solved(self):
        for i in range(self.BOARD_SIZE):
            if not self._check_each_cell(i):
                return False
        for i in range(self.BOARD_SIZE):
            if not self._check_each_column(i):
                return False
        for i in range(self.BOARD_SIZE):
            if not self._check_each_row(i):
                return False

        return True


class Game_Sudoku(Game):
    def __init__(self, start, goal):
        super(Game_Sudoku, self).__init__(start, goal)

    def solve(self):
        """solve the defined problem with A*

        Args:

        Returns:
            solved (bool): flag of success
            self.final_node: final node
        """
        presentNode = None
        solved = False

        while not self.openlist.isempty():
            presentNode = self.openlist.front()
            if presentNode._is_solved():
                solved = True
                break

            self.openlist.remove(presentNode)
            presentNode.moveall(self)

        self.final_node = presentNode

        return solved, self.final_node
