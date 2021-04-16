#include <bits/stdc++.h>
#include <vector>
using namespace std;
using P = pair<int, int>;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1160&lang=jp

void dfs(vector<vector<int>> &C, P p, int W, int H)
{
    int x = p.first;
    int y = p.second;
    C[y][x] = -1;
    int direction_x[8] = {0, 1, -1, 0, 1, 1, -1, -1};
    int direction_y[8] = {-1, 0, 0, 1, -1, 1, 1, -1};

    for (int i = 0; i < 8; i++)
    {
        int next_x = x + direction_x[i];
        int next_y = y + direction_y[i];
        if (0 <= next_x && next_x < W && 0 <= next_y && next_y < H)
        {
            if (C[next_y][next_x] == 1)
            {
                P next_p = make_pair(next_x, next_y);
                dfs(C, next_p, W, H);
            }
        }
    }
}

int main()
{
    bool flag = true;
    vector<int> ans;
    while (flag)
    {
        int W, H;
        cin >> W >> H;
        if (W == 0 && H == 0)
        {
            break;
        }
        vector<vector<int>> C(H, vector<int>(W, 0));
        for (int h = 0; h < H; h++)
        {
            for (int w = 0; w < W; w++)
            {
                cin >> C[h][w];
            }
        }
        int count = 0;
        for (int h = 0; h < H; h++)
        {
            for (int w = 0; w < W; w++)
            {
                if (C[h][w] == 1)
                {
                    dfs(C, make_pair(w, h), W, H);
                    count += 1;
                }
            }
        }
        ans.push_back(count);
    }

    for (auto a : ans)
        cout << a << endl;
}