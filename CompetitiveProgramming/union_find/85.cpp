#include <bits/stdc++.h>
#include <cmath>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A

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
    int n, q;
    cin >> n >> q;
    UnionTree ut(n);

    for (int i = 0; i < q; i++)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0)
        {
            ut.unite(x, y);
        }
        else if (c == 1)
        {
            if (ut.isSame(x, y))
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
}