#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc079/tasks/abc079_d

long long INF = 1LL << 60;

int main()
{
    int H, W;
    cin >> H >> W;
    long long cost[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cost[i][j] = INF;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cin >> cost[i][j];

    for (int k = 0; k < 10; k++)
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

    long long ans = 0;
    for (int h = 0; h < H; h++)
        for (int w = 0; w < W; w++)
        {
            int a;
            cin >> a;
            if (a != -1)
                ans += cost[a][1];
            else
                continue;
        }

    cout << ans << endl;
}