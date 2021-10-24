#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_A&lang=ja

void Binary(int x, vector<int> &bit, int N)
{
    for (int i = 0; i < N; i++)
    {
        int Div = (1 << i);
        bit[i] = (x / Div) % 2;
    }
}

bool judge(vector<int> A, int qi, int N)
{
    for (int i = 0; i < (1 << N); i++)
    {
        vector<int> bit(N, 0);
        Binary(i, bit, N);
        int ans = 0;
        for (int j = 0; j < N; j++)
        {
            if (bit[j] == 1)
            {
                ans += A[j];
                if (ans == qi)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int N;
    cin >> N;
    vector<int> A(N, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int qi;
        cin >> qi;
        if (judge(A, qi, N))
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
}