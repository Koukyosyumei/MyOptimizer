#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja

int LCS(string X, string Y)
{
    int len_x = X.length();
    int len_y = Y.length();
    int dp[len_x + 1][len_y + 1];
    for (int i = 0; i <= len_y; i++)
    {
        dp[0][i] = 0;
    }
    for (int j = 0; j <= len_x; j++)
    {
        dp[j][0] = 0;
    }

    for (int x = 1; x < len_x + 1; x++)
    {
        for (int y = 1; y < len_y + 1; y++)
        {
            if (X[x - 1] == Y[y - 1])
            {
                dp[x][y] = dp[x - 1][y - 1] + 1;
            }
            else
            {
                dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]);
            }
        }
    }

    return dp[len_x][len_y];
}

int main()
{
    int N;
    cin >> N;
    int results[N];
    for (int n = 0; n < N; n++)
    {
        string X, Y;
        cin >> X;
        cin >> Y;
        results[n] = LCS(X, Y);
    }
    for (int n = 0; n < N; n++)
    {
        cout << results[n] << endl;
    }
}
