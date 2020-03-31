#include <bits/stdc++.h>
using namespace std;
vector<int> cnt(100001);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        ++cnt[val];
    }

    for (int i = 0; i < 100001; i++)
    {
        for (int j = cnt[i]; j > 0; --j)
        {
            cout << i << "\n";
        }
    }
}