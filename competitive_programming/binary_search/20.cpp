#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
using namespace std;

//https://atcoder.jp/contests/abc077/tasks/arc084_a

int main()
{
    int N;
    cin >> N;
    vector<int> A(N, 0);
    vector<int> B(N, 0);
    vector<int> C(N, 0);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < N; i++)
        cin >> B[i];
    for (int i = 0; i < N; i++)
        cin >> C[i];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sort(C.begin(), C.end());

    int ans = 0;
    for (int p = 0; p < N; p++)
    {
        int b = B[p];

        auto a_max_it = upper_bound(A.begin(), A.end(), b - 1);
        int a_count = a_max_it - A.begin();

        auto c_min_it = lower_bound(C.begin(), C.end(), b + 1);
        int c_count = C.end() - c_min_it;

        ans += a_count * c_count;
    }
    cout << ans << endl;
}