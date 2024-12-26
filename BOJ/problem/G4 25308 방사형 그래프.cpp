// URL: https://www.acmicpc.net/problem/25308
// Algo: 기하학, 조합, 브루트포스

// Start:	241226 10 48
// Read:	0 2
// Think:	0 25
// Code:	0 5
// Total:   0 32

// https://burningfalls.github.io/algorithm/boj-25308/

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using ll = long long;
int arr[8];

bool Check(const ll a, const ll b, const ll c)
{
    return (a + c) * (a + c) * b * b >= 2 * a * a * c * c;
}

int main()
{
    fastio;

    for (int& num : arr) cin >> num;
    vector<int> comb = {0, 1, 2, 3, 4, 5, 6, 7};

    int answer = 0;
    do
    {
        bool success = true;
        for (int i = 0; i < 8; ++i)
        {
            const ll a = arr[comb[(i + 0) % 8]];
            const ll b = arr[comb[(i + 1) % 8]];
            const ll c = arr[comb[(i + 2) % 8]];
            if (!Check(a, b, c))
            {
                success = false;
                break;
            }
        }
        answer += success;
    }
    while (next_permutation(all(comb)));

    cout << answer;
}
