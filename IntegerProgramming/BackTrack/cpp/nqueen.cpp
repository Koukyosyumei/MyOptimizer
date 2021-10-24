#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
using namespace std;

#define N 12

int y2x[N];        // y2x[y] = x means that there is a queen at (x, y)
int num_solutions; // total number of solutions found so far
bool flag;

/**
 * Solve N-Queen with backtrack
 *
 * @param n すでに何行目までクイーンを置いているか
 */
void nqueen_backtracking(int n)
{
    for (int j = 0; j < N; ++j)
    {
        flag = true;
        for (int i = 0; i < n; ++i)
        {
            if (j == y2x[i] || abs(j - y2x[i]) == n - i)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            y2x[n] = j;
            if (n + 1 == N)
                ++num_solutions;
            else
                nqueen_backtracking(n + 1);
        }
    }
}

int main()
{
    num_solutions = 0;

    clock_t start, end;
    nqueen_backtracking(0);
    end = clock();

    cout << "total number of solutions is " << num_solutions << endl;
    printf("time = %f[s]", (double)(end - start) / CLOCKS_PER_SEC);
}