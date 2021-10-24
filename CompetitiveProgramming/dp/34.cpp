#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_9_A

int main()
{
    int N;
    cin >> N;
    int dp[N + 1];
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i < N + 1; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    cout << dp[N] << endl;
}