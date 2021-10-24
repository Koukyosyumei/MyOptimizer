#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja

struct Edge
{
    int to;
    int weight;
};
using Graph = vector<vector<Edge>>;

void bfs(Graph &G, vector<int> &dis, int s, int E)
{
    int d = 0;
    dis[s] = d;
    queue<int> que;
    que.push(s);
    int count = E;
    while (!que.empty() && count > 0)
    {
        int u = que.front();
        que.pop();
        for (auto e : G[u])
        {
            if (dis[e.to] == -1)
            {
                dis[e.to] = dis[u] + e.weight;
                que.push(e.to);
            }
            else
            {
                dis[e.to] = min(dis[e.to], dis[u] + e.weight);
                que.push(e.to);
            }
        }
        count = count - 1;
    }
}

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    Graph G(V);
    for (int i = 0; i < E; i++)
    {
        int s, t, d;
        cin >> s >> t >> d;
        G[s].push_back({t, d});
    }
    vector<int> dis(V, -1);
    bfs(G, dis, r, E);
    for (auto d : dis)
    {
        if (d == -1)
        {
            cout << "INF" << endl;
        }
        else
        {
            cout << d << endl;
        }
    }
}