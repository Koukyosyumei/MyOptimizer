#include <bits/stdc++.h>
#include <cmath>
using namespace std;

// https://qiita.com/e869120/items/eb50fdaece12be418faa#union-find-1

using P = pair<int, int>;

struct UnionTree
{
    vector<int> parents, size;
    UnionTree(int n)
    {
        parents.resize(n, 0);
        size.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            makeTree(i);
        }
    }

    void makeTree(int x)
    {
        parents[x] = x;
        size[x] = 1;
    }

    int findRoot(int x)
    {
        if (parents[x] != x)
        {
            parents[x] = findRoot(parents[x]);
        }
        return parents[x];
    }

    bool isSame(int x, int y)
    {
        return findRoot(x) == findRoot(y);
    }

    bool unite(int x, int y)
    {
        x = findRoot(x);
        y = findRoot(y);
        if (x == y)
        {
            return false;
        }
        else
        {
            if (size[x] > size[y])
            {
                parents[y] = x;
                size[x] += size[y];
            }
            else
            {
                parents[x] = y;
                size[y] += size[x];
            }
            return true;
        }
    }
};

int main()
{
    int N, M;
    cin >> N >> M;
    P ps[M];
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        ps[i] = make_pair(a - 1, b - 1);
    }

    int count = 0;
    for (int i = 0; i < M; i++)
    {
        UnionTree ut(N);
        for (int j = 0; j < M; j++)
            if (j != i)
                ut.unite(ps[j].first, ps[j].second);
        if (ut.size[ut.findRoot(0)] != N)
            count++;
    }
    cout << count << endl;
}