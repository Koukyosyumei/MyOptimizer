#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

//https://atcoder.jp/contests/abc128/tasks/abc128_c
//https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361

int main()
{
    int N, M;
    cin >> N >> M;
    long long S[M];
    for (int m = 0; m < M; m++)
    {
        int k;
        cin >> k;
        long long sm = 0;
        for (int i = 0; i < k; i++)
        {
            int s;
            cin >> s;
            sm |= (1 << (s - 1));
        }
        S[m] = sm;
    }

    int P[M];
    for (int m = 0; m < M; m++)
        cin >> P[m];

    long long ans = 0;
    for (int b = 0; b < (1 << N); b++)
    {
        int tento = 0;
        for (int m = 0; m < M; m++)
            if (__builtin_popcount(S[m] & b) % 2 == P[m])
                tento++;
        if (tento == M)
            ans++;
    }
    cout << ans << endl;
}