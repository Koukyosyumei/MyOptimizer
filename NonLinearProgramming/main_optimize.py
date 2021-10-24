from core import Func
from optimizer import GD, Newton
from sheduler import Backtrack

if __name__ == "__main__":
    func = Func(lambda xs: (xs[0] - 2) ** 4 + (xs[0] - 2 * xs[1]) ** 2)
    var_num = 2

    backtrack = Backtrack(func)
    gd = GD(func, var_num, backtrack, log=1)

    newton = Newton(func, var_num, log=1)

    x = [0, 3]
    print("SGD")
    x_optim, xdiff = gd.optimize(x)
    print("Newton")
    x_optim, xdiff = newton.optimize(x)
