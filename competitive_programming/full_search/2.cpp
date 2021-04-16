#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc106/tasks/abc106_b

int LIM = 200;

int main()
{
    int N;
    cin >> N;
    int count = 0;
    for (int n = 1; n <= N; n++)
    {
        if (n % 2 == 1)
        {
            int num = 0;
            for (int i = 1; i <= LIM; i++)
                if (n % i == 0)
                    num += 1;

            if (num == 8)
                count += 1;
        }
    }
    cout << count << endl;
}