#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define INF 1e9
const int MAXN = 16;

struct TSP
{
    int n, m;
    vector<vector<int>> distance;
    int dp[1 << MAXN][MAXN];
    vector<int> visit_order;

    TSP(int _n, int _m, vector<vector<int>> _d)
    {
        n = _n;
        m = _m;
        distance = _d;
    }

    int calculate_2opt_exchange_cost(int i, int j)
    {
        int a;
        if (i != 0)
            a = visit_order[i - 1];
        else
            a = visit_order[n - 1];
        int b = visit_order[(i) % n];
        int c = visit_order[j];
        int d = visit_order[(j + 1) % n];

        int cost_before = distance[a][b] + distance[c][d];
        int cost_after = distance[a][c] + distance[b][d];

        return cost_after - cost_before;
    }

    void apply_2opt_exchange(int i, int j)
    {
        vector<int> tmp(j - i + 1, 0);
        copy(visit_order.begin() + i, visit_order.begin() + j + 1, tmp.begin());
        reverse(tmp.begin(), tmp.end());
        for (int x = i; x < j + 1; x++)
        {
            visit_order[x] = tmp[x - i];
        }
    }

    bool improve_with_2opt()
    {
        int i_best, j_best;
        int cost_diff_best = 0;

        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 2; j < n; j++)
            {
                if ((i == 0) && (j == n - 1))
                    continue;

                int cost_diff = calculate_2opt_exchange_cost(i, j);

                if (cost_diff < cost_diff_best)
                {
                    cost_diff_best = cost_diff;
                    i_best = i;
                    j_best = j;
                }
            }
        }

        if (cost_diff_best < 0)
        {
            apply_2opt_exchange(i_best, j_best);
            return true;
        }
        else
        {
            return false;
        }
    }

    vector<int> local_search()
    {
        visit_order.resize(n);
        iota(visit_order.begin(), visit_order.end(), 0);
        while (true)
        {
            bool improved = improve_with_2opt();
            if (!improved)
                break;
        }
        return visit_order;
    }

    int bitDP()
    {
        fill((int *)dp, (int *)(dp + (1 << MAXN)), -1);
        return _bitsearch(0, 0);
    }

    int _bitsearch(int S, int v)
    {
        if (dp[S][v] >= 0)
            return dp[S][v];

        if (S == (1 << n) - 1 && v == 0)
            return dp[S][v] = 0;

        int tmp = INF;
        REP(u, n)
        {
            if (!(S >> u & 1))
                tmp = min(tmp, _bitsearch(S | 1 << u, u) + distance[v][u]);
        }
        return dp[S][v] = tmp;
    }
};

int main()
{
    int n;
    int m;
    cin >> n >> m;
    vector<vector<int>> d;
    d.assign(n, vector<int>(n, 0));
    REP(i, n)
    {
        REP(j, n) { d[i][j] = d[j][i] = INF; }
    }
    REP(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = c;
        d[b][a] = c;
    }
    TSP tsp(n, m, d);

    tsp.local_search();
    cout << "local search (2 opt)" << endl;
    cout << "route: ";
    for (auto e : tsp.visit_order)
    {
        cout << e << " ";
    }
    cout << endl;
    int local_search_cost = 0;
    for (int i = 0; i < n; i++)
    {
        local_search_cost += d[tsp.visit_order[i]][tsp.visit_order[(i + 1) % n]];
    }
    cout << "cost: " << local_search_cost << endl;
    cout << "-----" << endl;

    cout << "bitDP" << endl;
    cout << "cost: " << tsp.bitDP() << endl;
}