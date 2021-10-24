from matplotlib import pyplot as plt

from core import Func
from visualize import vis, vis2

if __name__ == "__main__":
    f1 = lambda xs: 2 * xs[0]
    f2 = lambda xs: xs[0] ** 2
    f3 = lambda xs: xs[0] ** 3
    f4 = lambda xs: xs[0] ** 2 + xs[0]
    f5 = lambda xs: 2 ** xs[0]
    f6 = lambda xs: xs[0] ** 2 + xs[1] ** 2
    f7 = lambda xs: xs[0] ** 2 + xs[0] * xs[1]

    xs = [[i / 5] for i in range(-15, 16)]

    plt.figure(figsize=(12, 6))
    plt.subplot(231)
    vis(f1, 0, xs)
    plt.subplot(232)
    vis(f2, 0, xs)
    plt.subplot(233)
    vis(f3, 0, xs)
    plt.subplot(234)
    vis(f4, 0, xs)
    plt.subplot(235)
    vis(Func(f4).grad(0), 0, xs)
    plt.subplot(236)
    vis(f5, 0, xs)

    plt.show()

    xsxs = [[i / 5, i / 5] for i in range(-15, 16)]
    plt.figure(figsize=(12, 6))

    plt.subplot(231)
    vis2(f6, 0, xsxs, False)
    plt.subplot(232)
    vis2(f6, 0, xsxs, True)
    plt.subplot(233)
    vis2(f6, 1, xsxs, True)
    plt.subplot(234)
    vis2(f7, 0, xsxs, False)
    plt.subplot(235)
    vis2(f7, 0, xsxs, True)
    plt.subplot(236)
    vis2(f7, 1, xsxs, True)

    plt.show()
