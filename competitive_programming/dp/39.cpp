#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/joi2011yo/tasks/joi2011yo_d

int main()
{
    int N;
    cin >> N;
    int xs[N - 1];
    for (int i = 0; i < N - 1; i++)
        cin >> xs[i];
    int res = 0;
    cin >> res;

    vector<vector<long long>> dp(N, vector<long long>(21, 0));
    dp[0][0] = 1;
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j <= 20; j++)
        {
            if (j - xs[i - 1] >= 0)
            {
                dp[i][j] += dp[i - 1][j - xs[i - 1]];
            }
            if (j + xs[i - 1] <= 20)
            {
                dp[i][j] += dp[i - 1][j + xs[i - 1]];
            }
        }
    }
    /*
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= 20; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    */

    cout << dp[N - 1][res] << endl;
}