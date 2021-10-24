#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

//https://atcoder.jp/contests/abc002/tasks/abc002_4

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N, vector<int>(N, 0));
    for (int m = 0; m < M; m++)
    {
        int x, y;
        cin >> x >> y;
        G[x - 1][y - 1] = 1;
        G[y - 1][x - 1] = 1;
    }
    for (int n = 0; n < N; n++)
        G[n][n] = 1;

    int ans = 0;
    for (int b = 0; b < (1 << N); b++)
    {
        vector<int> S;
        for (int n = 0; n < N; n++)
            if (b & (1 << n))
                S.push_back((n));

        bool flag = true;
        for (auto s1 : S)
            for (auto s2 : S)
                if (G[s1][s2] != 1)
                    flag = false;
        if (flag)
            ans = max(ans, __builtin_popcount(b));
    }

    cout << ans << endl;
}