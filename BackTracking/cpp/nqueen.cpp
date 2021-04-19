#include <stdio.h>
#include <time.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define N 8

struct nQueen
{
    vector<vector<bool>> board;
    int n;
    int resolve;
    nQueen(int nrows)
    {
        n = nrows;
        resolve = 0;
        board.assign(n, vector<bool>(n, false));
    }

    void printBoard()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j])
                    printf("Q");
                else
                    printf("*");
            }
            printf("\n");
        }
        printf("\n\n");
    }

    /*
    Determine if there are any other queens in the specified direction.
    * i：Queen's position row number
    * j：Queen's position column number
    * di：Increment of row number
    * dj：Increment of column number
    */
    bool checkExist(int i, int j, int di, int dj)
    {
        for (int k = 1; k < n; k++)
        {
            int ii = i + di * k;
            int jj = j + dj * k;
            if (ii >= n || ii < 0 || jj >= n || jj < 0)
                break;
            if (board[ii][jj])
                return false;
        }
        return true;
    }

    /*
     Determine if the N queens problem is met.
    */
    bool checknQueen()
    {
        int dxs[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
        int dys[8] = {0, 0, -1, 1, -1, 1, -1, 1};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int d = 0; d < 8; d++)
                    if (board[i][j])
                        if (!checkExist(i, j, dxs[d], dys[d]))
                            return false;
        return true;
    }

    /*
     * Installation of queens
     * q：number of queens already placed
     * k: start location 
    */
    void fullsearch(int q, int k)
    {
        if (q == n)
        {
            // If you have already installed n queens
            if (checknQueen())
            {
                resolve++;
                printBoard();
            }
            return;
        }

        // place the queens
        for (int loc = k; loc < n * n; loc++)
        {
            int i = loc / n;
            int j = loc % n;

            board[i][j] = true;
            fullsearch(q + 1, loc + 1);
            board[i][j] = false;
        }
    }

    void backtrack(int q, int k)
    {
        if (q == n)
        {
            // If you have already installed n queens
            if (checknQueen())
            {
                resolve++;
                printBoard();
            }
            return;
        }

        // place the queens
        for (int loc = k; loc < n * n; loc++)
        {
            int i = loc / n;
            int j = loc % n;

            board[i][j] = true;
            if (checknQueen())
            {
                backtrack(q + 1, loc + 1);
            }
            board[i][j] = false;
        }
    }
};

int main()
{
    clock_t start, end;
    nQueen nq(8);
    start = clock();
    nq.backtrack(0, 0);
    cout << "total number of solutions is " << nq.resolve << endl;
    end = clock();
    printf("time = %f[s]", (double)(end - start) / CLOCKS_PER_SEC);
}