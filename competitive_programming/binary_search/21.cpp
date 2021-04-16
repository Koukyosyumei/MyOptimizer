#include <bits/stdc++.h>
using namespace std;

//https://algo-logic.info/abc023d/

bool judge(long long X, int N, vector<long long> H, vector<long long> S)
{
    vector<long long> count(N, 0);
    for (int i = 0; i < N; i++)
    {
        // potential_time以内に撃ち落さなければいけない
        int potential_time = floor((X - H[i]) / S[i]);
        potential_time = min(N - 1, potential_time);
        count[potential_time] += 1;
    }

    for (int i = 0; i < N - 1; i++)
        count[i + 1] += count[i];

    for (int i = 0; i < N; i++)
        if (count[i] > i + 1)
            return false;
    return true;
}

int main()
{
    int N;
    cin >> N;
    vector<long long> H(N, 0);
    vector<long long> S(N, 0);
    long long max_x, min_x;
    max_x = 0;
    min_x = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> H[i] >> S[i];
        long long temp_x = H[i] + S[i] * (N - 1);
        max_x = max(max_x, temp_x);
        min_x = max(min_x, H[i]);
    }

    long long left = min_x;
    long long right = max_x;

    while (left <= right)
    {
        long long mid = left + (right - left) / 2;
        if (judge(mid, N, H, S))
            right = mid - 1;
        else
            left = mid + 1;
    }

    cout << left << endl;
}