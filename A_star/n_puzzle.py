import copy

from core import Game, Node


class Node_N_Puzzle(Node):
    def __init__(self, pattern, gfunc,
                 move="start", nrow=3,
                 weight=1):

        self.pattern = pattern
        self.gfunc = gfunc
        self.weight = weight
        self.move = move
        self.nrow = nrow

        for (row, i) in zip(pattern, range(self.nrow)):
            if 0 in row:
                self.blankloc = [i, row.index(0)]

    def __eq__(self, other):
        if other is None:
            return False

        if not isinstance(other, type(self)):
            raise TypeError(f"other should be {type(self)}")

        return self.pattern == other.pattern

    def __getitem__(self, key):
        if not isinstance(key, tuple):
            raise TypeError("Key should be tuple")

        if len(key) != 2:
            raise KeyError(f"length of key must be 2, not {len(key)}")

        return self.pattern[key[0]][key[1]]

    def calc_hfunc(self, goal):
        self.hfunc = 0
        for i in range(self.nrow):
            for j in range(self.nrow):
                if self.pattern[i][j] != goal.pattern[i][j]:
                    self.hfunc += 1

        if self.blankloc != goal.blankloc:
            self.hfunc -= 1

        self.ffunc = self.gfunc + self.weight*self.hfunc

        return self.hfunc, self.gfunc, self.ffunc

    def moveleft(self):
        if self.blankloc[1] == 0:
            return None

        left = copy.deepcopy(self.pattern)
        left[self.blankloc[0]][self.blankloc[1]
                               ] = left[self.blankloc[0]][self.blankloc[1]-1]
        left[self.blankloc[0]][self.blankloc[1]-1] = 0

        return Node_N_Puzzle(left, self.gfunc+1, 'left')

    def moveright(self):
        if self.blankloc[1] == 2:
            return None

        right = copy.deepcopy(self.pattern)
        right[self.blankloc[0]][self.blankloc[1]
                                ] = right[self.blankloc[0]][self.blankloc[1]+1]
        right[self.blankloc[0]][self.blankloc[1]+1] = 0

        return Node_N_Puzzle(right, self.gfunc+1, 'right')

    def moveup(self):
        if self.blankloc[0] == 0:
            return None

        up = copy.deepcopy(self.pattern)
        up[self.blankloc[0]][self.blankloc[1]
                             ] = up[self.blankloc[0]-1][self.blankloc[1]]
        up[self.blankloc[0]-1][self.blankloc[1]] = 0

        return Node_N_Puzzle(up, self.gfunc+1, 'up')

    def movedown(self):
        if self.blankloc[0] == 2:
            return None

        down = copy.deepcopy(self.pattern)
        down[self.blankloc[0]][self.blankloc[1]
                               ] = down[self.blankloc[0]+1][self.blankloc[1]]
        down[self.blankloc[0]+1][self.blankloc[1]] = 0

        return Node_N_Puzzle(down, self.gfunc+1, 'down')

    def moveall(self, game):
        movelist = ["moveleft", "moveright", "moveup", "movedown"]
        next_nodes = []
        for move in movelist:
            next_node = getattr(self, move)()
            next_node = None if game.closedlist.isclosed(
                next_node) else next_node
            game.openlist.insert(next_node)
            next_nodes.append(next_node)

        game.closedlist.insert(self)

        return next_nodes

    def print(self):
        print(f"move: {self.move}, gfunc: {self.gfunc}")
        for i in range(self.nrow):
            print(self.pattern[i])


class Game_N_Puzzle(Game):
    def __init__(self, start, goal):
        super(Game_N_Puzzle, self).__init__(start, goal)

    def print_path(self):
        move_reverse = {"up": "movedown",
                        "down": "moveup",
                        "right": "moveleft",
                        "left": "moveright"}

        presentNode = self.final_node
        while presentNode.move != "start":
            presentNode.print()
            presentNode = getattr(
                presentNode, move_reverse[presentNode.move])()

            for i in self.closedlist.\
                    nodes[self.closedlist.idx_formula(presentNode)]:
                if i == presentNode:
                    presentNode = i
