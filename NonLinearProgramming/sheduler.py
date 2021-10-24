import copy

from core import Func


class Scheduler:
    def __init__(self, func, init_alpha):
        self.func = func
        self.init_alpha = init_alpha

    def schedule(self):
        pass


class Backtrack(Scheduler):
    def __init__(self, func, tau=0.5, beta=0.01, maxitr=100):
        super().__init__(func, 1)
        self.tau = tau
        self.beta = beta
        self.maxitr = maxitr

    def schedule(self, x, d):
        def g(alp):
            x_new = copy.deepcopy(x)
            for i in range(len(x_new)):
                x_new[i] += alp[0] * d[i]

            return self.func(x_new)

        g_obj = Func(g)
        g_0 = g_obj([0])
        g_grad_0 = g_obj.grad(0)([0])

        cnt = self.maxitr
        alpha = 1
        while g_obj([alpha]) > g_0 + self.tau * g_grad_0 * alpha:
            alpha *= self.beta
            cnt -= 1
            if cnt == 0:
                break

        return alpha
