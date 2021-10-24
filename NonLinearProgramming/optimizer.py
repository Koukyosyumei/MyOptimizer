import copy

import numpy as np


class Optimizer:
    def __init__(self, func, var_num, maxitr=100):
        self.func = func
        self.var_num = var_num
        self.maxitr = maxitr
        self.grads = [func.grad(var_id) for var_id in range(var_num)]

    def optimize(self):
        pass


class SGD(Optimizer):
    def __init__(self, func, var_num, scheduler, maxitr=100, log=10):
        super().__init__(func, var_num, maxitr=maxitr)
        self.scheduler = scheduler
        self.log = log

    def optimize(self, init_x):
        x = copy.deepcopy(init_x)
        xdiff = []

        for i in range(self.maxitr):
            temp_x = copy.deepcopy(x)
            d = [0] * self.var_num

            for var_id in range(self.var_num):
                d[var_id] = -1 * self.grads[var_id](temp_x)

            alpha = self.scheduler.schedule(temp_x, d)
            for var_id in range(self.var_num):
                x[var_id] += alpha * d[var_id]

            xdiff.append([x[var_id] - temp_x[var_id] for var_id in range(self.var_num)])

            if self.log > 0 and i % self.log == 0:
                print("i is ", i)
                print("alpha is ", alpha)
                print("direction is ", d)
                print("x is ", x)
                print("---")
                print("")

        return x, xdiff


class Newton(Optimizer):
    def __init__(self, func, var_num, maxitr=100, log=10):
        super().__init__(func, var_num, maxitr=maxitr)
        self.log = log

    def optimize(self, init_x):
        x = copy.deepcopy(init_x)
        xdiff = []

        for i in range(self.maxitr):
            temp_x = copy.deepcopy(x)

            g = [0] * self.var_num
            for var_id in range(self.var_num):
                g[var_id] = -1 * self.grads[var_id](temp_x)

            h = self.func.hessian(temp_x)
            d = np.linalg.inv(h).dot(g)

            for var_id in range(self.var_num):
                x[var_id] += d[var_id]

            xdiff.append([x[var_id] - temp_x[var_id] for var_id in range(self.var_num)])

            if self.log > 0 and i % self.log == 0:
                print("i is ", i)
                print("direction is ", d)
                print("x is ", x)
                print("---")
                print("")

        return x, xdiff
