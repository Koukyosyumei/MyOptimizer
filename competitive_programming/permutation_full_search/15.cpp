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
    int Y[N];
    for (int i = 0; i < N; i++)
        cin >> X[i] >> Y[i];

    int town[N];
    for (int i = 0; i < N; i++)
        town[i] = i;

    double sum_d = .0;
    int count = 0;
    do
    {
        double temp_sum_d = .0;
        for (int i = 0; i < N - 1; i++)
        {
            double temp_x = pow(X[town[i]] - X[town[i + 1]], 2);
            double temp_y = pow(Y[town[i]] - Y[town[i + 1]], 2);
            double temp_d = sqrt(temp_x + temp_y);
            temp_sum_d += temp_d;
        }
        sum_d += temp_sum_d;
        count += 1;
    } while (next_permutation(town, town + N));
    cout << count << endl;
    cout << sum_d / count << endl;
}