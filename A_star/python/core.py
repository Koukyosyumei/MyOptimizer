from abc import ABC, abstractmethod

from datastructure import ClosedList, OpenList


class Node(ABC):

    @abstractmethod
    def __eq__(self, other):
        pass

    @abstractmethod
    def __getitem__(self, key):
        pass

    @abstractmethod
    def calc_hfunc(self, goal):
        pass

    @abstractmethod
    def moveall(self, game):
        pass

    @abstractmethod
    def print(self):
        pass


class Game:

    def __init__(self, start, goal):
        """
        Args:
            start (Node): start node
            goal (Node): goal node

        Attributes:
            start (Node): start node
            goal (Node): goal node
            openlist (OpenList): open list
            closedlist (ClosedList): close list
            final_node (Node): the fianl node which the solver reached
        """
        self.start = start
        self.goal = goal

        def idx_formula_open(node): return node.calc_hfunc(self.goal)[2]
        def idx_formula_closed(node): return node.calc_hfunc(self.goal)[0]
        self.openlist = OpenList(idx_formula_open)
        self.closedlist = ClosedList(idx_formula_closed)

        self.openlist.insert(start)
        self.final_node = None

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
            if presentNode == self.goal:
                solved = True
                break

            self.openlist.remove(presentNode)
            presentNode.moveall(self)

        self.final_node = presentNode

        return solved, self.final_node
