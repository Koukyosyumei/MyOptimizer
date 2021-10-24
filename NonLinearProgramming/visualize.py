from matplotlib import pyplot as plt

from core import Func


def vis(f, var_idx, xs):
    func = Func(f)
    ys = [func(x) for x in xs]
    plt.plot(xs, ys, label="f")

    g = func.grad(var_idx)
    y_ps = [g(x) for x in xs]
    plt.plot(xs, y_ps, label="grad")

    plt.legend()
    plt.grid()


def vis2(f, var_idx, xs, grad=False):
    x1 = [x[0] for x in xs]
    x2 = [x[1] for x in xs]

    func = Func(f)
    if not grad:
        ys = [[func([f, s]) for s in x2] for f in x1]
        plt.contour(x1, x2, ys)
    else:
        g = func.grad(var_idx)
        y_ps = [[g([f, s]) for s in x2] for f in x1]
        plt.contour(x1, x2, y_ps)

    plt.grid()
