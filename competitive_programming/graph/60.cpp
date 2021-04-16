#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=ja

const long long INF = 1LL << 60;

int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<long long>> dp(V, vector<long long>(V, INF));
    for (int v = 0; v < V; v++)
    {
        dp[v][v] = 0;
    }
    for (int e = 0; e < E; e++)
    {
        long long s0, t0, d0;
        cin >> s0 >> t0 >> d0;
        dp[s0][t0] = d0;
    }

    bool negative_flag = false;
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    bool negative_circle_flag = false;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dp[i][i] < 0)
            {
                negative_circle_flag = true;
            }
        }
    }

    if (negative_circle_flag)
    {
        cout << "NEGATIVE CRICLE" << endl;
    }
    else
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dp[i][j] > 1LL << 59)
                {
                    cout << "INF"
                         << " ";
                }
                else
                {
                    cout << dp[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
}