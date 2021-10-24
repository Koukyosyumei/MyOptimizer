import heapq


class OpenList:

    def __init__(self, idx_formula):
        self.indices = []
        self.nodes = {}
        self.idx_formula = idx_formula

    def isempty(self):
        return len(self.indices) == 0

    def insert(self, node):
        if node is None:
            return

        idx = self.idx_formula(node)
        if idx not in self.indices:
            heapq.heappush(self.indices, idx)

        if idx in self.nodes:
            self.nodes[idx].append(node)
        else:
            self.nodes[idx] = [node]

    def remove(self, node):
        if node is None:
            return

        idx = self.idx_formula(node)
        self.nodes[idx].remove(node)
        if len(self.nodes[idx]) == 0:
            del self.nodes[idx]
            heapq.heappop(self.indices)

    def front(self):
        return self.nodes[self.indices[0]][-1]


class ClosedList:

    def __init__(self, idx_formula):
        self.indices = []
        self.nodes = {}
        self.idx_formula = idx_formula

    def insert(self, node):
        if node is None:
            return

        idx = self.idx_formula(node)
        heapq.heappush(self.indices, idx)
        if idx in self.nodes:
            self.nodes[idx].append(node)
        else:
            self.nodes[idx] = [node]

    def isclosed(self, node):
        if node is None:
            return True

        idx = self.idx_formula(node)

        if idx in self.nodes:
            for x in self.nodes[idx]:
                if x == node:
                    return True

        return False
