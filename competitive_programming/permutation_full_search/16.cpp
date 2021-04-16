#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int X[N];
    int P[N];
    int Q[N];
    for (int n = 0; n < N; n++)
        X[n] = n + 1;
    for (int n = 0; n < N; n++)
        cin >> P[n];
    for (int n = 0; n < N; n++)
        cin >> Q[n];
    int a = 0;
    int b = 0;
    do
    {
        a++;
        bool flag = true;
        for (int i = 0; i < N; i++)
        {
            if (X[i] != P[i])
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
            break;
    } while (next_permutation(X, X + N));

    for (int n = 0; n < N; n++)
        X[n] = n + 1;
    do
    {
        b++;
        bool flag = true;
        for (int i = 0; i < N; i++)
        {
            if (X[i] != Q[i])
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
            break;
    } while (next_permutation(X, X + N));

    cout << abs(b - a) << endl;
}