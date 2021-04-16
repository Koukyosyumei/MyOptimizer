#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
using namespace std;

//https://atcoder.jp/contests/abc122/tasks/abc122_b

int main()
{
    string str;
    cin >> str;
    int len = str.length();
    int max_len = 0;
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len - i + 1; j++)
        {
            string ss = str.substr(i, j);
            bool flag = true;
            for (int k = 0; k < j; k++)
            {
                if ((ss[k] != 'A') && (ss[k] != 'C') && (ss[k] != 'G') && (ss[k] != 'T'))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                int ss_len = ss.length();
                max_len = max(max_len, ss_len);
            }
        }

    cout << max_len << endl;
}