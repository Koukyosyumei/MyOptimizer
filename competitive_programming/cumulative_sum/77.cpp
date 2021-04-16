#include <bits/stdc++.h>
#include <cmath>
using namespace std;

//https://atcoder.jp/contests/joi2010ho/tasks/joi2010ho_a

const long long MOD = 100000;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<long long> dist(N, 0);
    vector<long long> S(N + 1, 0);
    for (int n = 1; n < N; n++)
    {
        cin >> dist[n];
    }
    for (int n = 1; n < N + 1; n++)
    {
        S[n] = S[n - 1] + dist[n - 1];
    }

    vector<long long> A(M, 0);
    long long ans = 0;
    int now = 1;
    int next;
    for (int m = 0; m < M; m++)
    {
        cin >> A[m];
        next = now + A[m];
        ans += abs(S[next] - S[now]) % MOD;
        now = next;
    }
    cout << ans % MOD << endl;
}