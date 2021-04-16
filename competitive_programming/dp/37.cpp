#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_A&lang=ja

int main()
{
    int N, M;
    cin >> N >> M;
    int C[M];
    for (int m = 0; m < M; m++)
    {
        cin >> C[m];
    }
    int dp[N + 1];
    int INF = 500000;
    dp[0] = 0;
    dp[1] = 1;
    for (int n = 2; n < N + 1; n++)
    {

        int min_num = INF;
        for (int m = 0; m < M; m++)
        {
            if (n - C[m] >= 0)
            {
                min_num = min(min_num, dp[n - C[m]] + 1);
            }
        }
        dp[n] = min_num;
    }
    cout << dp[N] << endl;
}