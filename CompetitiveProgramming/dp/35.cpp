#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B

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
        for (int j = 0; j < W + 1; j++)
            dp[i][j] = 0;

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 0; j < W + 1; j++)
        {
            if (j >= w[i])
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    int ans = 0;
    for (int j = 0; j < W + 1; j++)
    {
        ans = max(ans, dp[N][j]);
    }
    cout << ans << endl;
}