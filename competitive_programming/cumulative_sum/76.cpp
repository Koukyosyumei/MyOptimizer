#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_a

int main()
{
    int N;
    cin >> N;
    long long A[N];
    vector<long long> S(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        S[i + 1] = S[i] + A[i];
    }

    for (int k = 1; k < N + 1; k++)
    {
        long long max_sum = 0;
        for (int j = k; j < N + 1; j++)
        {
            long long temp = S[j] - S[j - k];
            max_sum = max(max_sum, temp);
        }
        cout << max_sum << endl;
    }
}