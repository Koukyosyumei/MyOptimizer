import copy

EPS = 1e-4


class Func:
    def __init__(self, f):
        self.f = f

    def __call__(self, xs):
        return self.f(xs)

    def grad(self, var_idx):
        def central_diff(xs):
            xs_forward = copy.deepcopy(xs)
            xs_backward = copy.deepcopy(xs)
            xs_forward[var_idx] = xs[var_idx] + EPS
            xs_backward[var_idx] = xs[var_idx] - EPS
            return (self.f(xs_forward) - self.f(xs_backward)) / (2 * EPS)

        return Func(central_diff)

    def hessian(self, xs):
        h_f = [[self.grad(i).grad(j) for j in range(len(xs))] for i in range(len(xs))]
        h = [[h_f[i][j](xs) for j in range(len(xs))] for i in range(len(xs))]

        return h
