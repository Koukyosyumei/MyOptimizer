import numpy as np


class SimpleSolver:
    def __init__(self, A, b, N_idx, B_idx, C):
        self.A = A
        self.b = b
        self.N_idx = N_idx
        self.B_idx = B_idx
        self.C = C

        self.x_B = np.zeros(len(B_idx))
        self.x_N = np.zeros(len(N_idx))

    def solve(self, max_iter=100):
        optimal_solution = np.zeros(len(self.B_idx) + len(self.N_idx))

        for itr in range(max_iter):
            print("N_idx is ", [i + 1 for i in self.N_idx])
            print("B_idx is ", [i + 1 for i in self.B_idx])

            b_hat = np.linalg.inv(self.A[:, self.B_idx]).dot(self.b)
            print("b_hat is ", b_hat)

            c_hat_N = self.C[self.N_idx] - self.A[:, self.N_idx].T.dot(
                np.linalg.inv(self.A[:, self.B_idx]).T
            ).dot(self.C[self.B_idx])
            print("c_hat_N is", c_hat_N)
            if np.max(c_hat_N) <= 0:
                z = self.C[self.B_idx].T.dot(b_hat)
                optimal_solution[self.B_idx] = b_hat
                print("Done!")
                print("optimal z is ", z)
                print("optimal solution is ", optimal_solution)

                break

            k = np.where(c_hat_N > 0)[0][-1]

            a_hat_k = self.A[:, self.N_idx][:, k]
            print("a_hat_k", a_hat_k)
            if np.max(a_hat_k) <= 0:
                break

            temp_thetas = [b_hat[i] / a_ik for i, a_ik in enumerate(a_hat_k)]
            min_i = np.argmin(temp_thetas)
            theta = temp_thetas[min_i]

            self.x_N[k] = theta
            self.x_B = b_hat - theta * a_hat_k

            print(f"swap x_{self.B_idx[min_i]+1} ans x_{self.N_idx[k]+1}")
            temp_i = self.B_idx[min_i]
            temp_k = self.N_idx[k]
            self.B_idx[min_i] = temp_k
            self.N_idx[k] = temp_i

            temp_x_i = self.x_B[min_i]
            temp_x_k = self.x_N[k]
            self.x_B[min_i] = temp_x_k
            self.x_N[k] = temp_x_i
            print("x_B is ", self.x_B)
            print("x_N is ", self.x_N)

        return optimal_solution, z


if __name__ == "__main__":
    print("example")
    A = np.array([[1, 1, 1, 0, 0], [1, 3, 0, 1, 0], [2, 1, 0, 0, 1]])
    b = np.array([6, 12, 10])
    B_idx = [2, 3, 4]
    N_idx = [0, 1]
    C = np.array([1, 2, 0, 0, 0])
    simplexsolver = SimpleSolver(A, b, N_idx, B_idx, C)
    simplexsolver.solve()

    print("2.4.1")
    A = np.array([[1, 1, 1, 1, 0, 0], [3, 4, 6, 0, 1, 0], [4, 5, 3, 0, 0, 1]])
    b = np.array([20, 100, 100])
    B_idx = [3, 4, 5]
    N_idx = [0, 1, 2]
    C = np.array([4, 8, 10, 0, 0, 0])
    simplexsolver = SimpleSolver(A, b, N_idx, B_idx, C)
    simplexsolver.solve()

    print("2.4.3")
    A = np.array([[1, 0, 1, 0], [20, 1, 0, 1]])
    b = np.array([1, 100])
    B_idx = [2, 3]
    N_idx = [0, 1]
    C = np.array([10, 1, 0, 0])
    simplexsolver = SimpleSolver(A, b, N_idx, B_idx, C)
    simplexsolver.solve()
