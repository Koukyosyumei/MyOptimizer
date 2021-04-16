#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja

int main()
{
    int N, W;
    cin >> N >> W;
    int v[N + 1];
    int w[N + 1];
    v[0] = 0;
    w[0] = 0;
    for (int i = 1; i < N + 1; i++)
    {
        cin >> v[i] >> w[i];
    }

    int dp[N + 1][W + 1];
    for (int i = 0; i < N + 1; i++)
        dp[i][0] = 0;
    for (int j = 0; j < W + 1; j++)
        dp[0][j] = 0;

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < W + 1; j++)
        {
            int m = j / w[i];
            int temp = 0;
            for (int p = 0; p <= m; p++)
            {
                temp = max(temp, dp[i - 1][j - w[i] * p] + v[i] * p);
            }
            dp[i][j] = temp;
        }
    }

    cout << dp[N][W] << endl;
}