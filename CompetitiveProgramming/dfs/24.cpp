#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to;
};
using Graph = vector<vector<Edge>>;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_B

void dfs(Graph &G, vector<int> &check, vector<int> &done, int s, int &t)
{
    check[s] = t;
    for (auto e : G[s])
    {
        if (check[e.to] == -1)
        {
            t += 1;
            dfs(G, check, done, e.to, t);
        }
    }
    done[s] = ++t;
}

int main()
{
    int N;
    cin >> N;
    Graph G(N);
    Graph G_r(N);
    vector<int> check(N, -1);
    vector<int> done(N, -1);
    for (int i = 0; i < N; i++)
    {
        int u, k;
        cin >> u >> k;
        for (int j = 0; j < k; j++)
        {
            int v;
            cin >> v;
            G[u - 1].push_back({v - 1});
            G_r[v - 1].push_back({u - 1});
        }
    }
    int t = 1;
    for (int i = 0; i < N; i++)
    {
        if (check[i] == -1)
        {
            dfs(G, check, done, i, t);
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << " " << check[i] << " " << done[i] << endl;
    }
}