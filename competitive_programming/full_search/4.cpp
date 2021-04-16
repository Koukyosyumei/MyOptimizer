#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc095/tasks/arc096_a

long long zero = 0;
long long min_cost = 10000000000000;

int main()
{
    long long A, B, C, X, Y;
    cin >> A >> B >> C >> X >> Y;
    long long lim = max(X, Y);
    for (int c = 0; c < lim + 1; c++)
    {
        int a = max(X - c, zero);
        int b = max(Y - c, zero);

        long long cost = A * a + B * b + 2 * C * c;
        min_cost = min(cost, min_cost);
    }

    cout << min_cost << endl;
}