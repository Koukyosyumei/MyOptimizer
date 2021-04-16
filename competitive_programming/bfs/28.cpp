#include <bits/stdc++.h>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C

struct Edge
{
    int to;
};
using Graph = vector<vector<Edge>>;

void bfs(Graph &G, vector<int> &dis, int s)
{
    int d = 0;
    dis[s] = d;
    queue<int> que;
    que.push(s);
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        for (auto e : G[u])
        {
            if (dis[e.to] == -1)
            {
                dis[e.to] = dis[u] + 1;
                que.push(e.to);
            }
        }
    }
}

int main()
{
    int N;
    cin >> N;
    Graph G(N);
    for (int i = 0; i < N; i++)
    {
        int u, K;
        cin >> u >> K;
        for (int k = 0; k < K; k++)
        {
            int v;
            cin >> v;
            G[u - 1].push_back({v - 1});
        }
    }

    vector<int> dis(N, -1);
    bfs(G, dis, 0);
    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << " " << dis[i] << endl;
    }
}