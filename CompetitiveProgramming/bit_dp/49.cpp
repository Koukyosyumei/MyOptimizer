#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to;
    int cost;
};
using Graph = vector<vector<Edge>>;
const int INF = 1000100100;
int bitdp(Graph &G, int s, int v)
{
    if (s == 0)
    {
        if (v == 0)
        {
            return 0;
        }
        else
        {
            return INF;
        }
    }

    if (s & (1 << v) == 0)
    {
        return INF;
    }

    int ret = INF;
    cout << v << endl;
    for (auto e : G[v])
    {
        int u = e.to;
        int temp = bitdp(G, s ^ (1 << v), u) + e.cost;
        ret = min(temp, ret);
    }
    return ret;
}

int main()
{
    int V, E;
    cin >> V >> E;
    Graph G(V);
    vector<vector<int>> dp((1 << V), vector<int>(V, 0));
    for (int e = 0; e < E; e++)
    {
        int s, t, d;
        cin >> s >> t >> d;
        G[s].push_back({t, d});
    }
    int ans = bitdp(G, (1 << V) - 1, 0);
    if (ans == INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}