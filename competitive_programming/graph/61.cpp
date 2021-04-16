#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc012/tasks/abc012_4

const long long INF = 1LL << 60;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<long long>> dp(N, vector<long long>(N, INF));
    for (int m = 0; m < M; m++)
    {
        int a, b, t;
        cin >> a >> b >> t;
        dp[a - 1][b - 1] = t;
        dp[b - 1][a - 1] = t;
    }
    for (int n = 0; n < N; n++)
        dp[n][n] = 0;

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    long long min_dist = INF;
    int min_idx = 0;
    for (int i = 0; i < N; i++)
    {
        long long temp = 0;
        for (int j = 0; j < N; j++)
            temp = max(temp, dp[i][j]);
        if (min_dist > temp)
        {
            min_dist = temp;
            min_idx = i;
        }
    }
    cout << min_dist << endl;
}