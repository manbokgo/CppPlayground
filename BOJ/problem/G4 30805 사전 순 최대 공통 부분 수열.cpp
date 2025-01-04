// URL: https://www.acmicpc.net/problem/30805
// Algo: 그리디

// Start:	250104 17 36
// Read:	0 2
// Think:	0 6
// Code:	0 20
// Total:	0 28

// n이 충분히 작으므로 무식한 방법으로 풀었다. 배열에서 최댓값을 뽑아서, 같지 않다면 그 원소를 erase해주고
// 같다면 각 배열에서 그 위치까지 모두 erase 해주는 걸 반복한다.

// 무식하게 하고 싶지 않다면 각 원소에 인덱스 데이터를 붙인 후, 내림차순으로 정렬해서 풀 수도 있다.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n, m;

    cin >> n;
    vector<int> a(n);
    for (auto& num : a) cin >> num;

    cin >> m;
    vector<int> b(m);
    for (auto& num : b) cin >> num;

    vector<int> ans;
    while (true)
    {
        if (a.empty() || b.empty())
            break;

        const auto iterA = max_element(all(a));
        const int maxA = *iterA;
        const int idxA = iterA - a.begin();

        const auto iterB = max_element(all(b));
        const int maxB = *iterB;
        const int idxB = iterB - b.begin();

        if (maxA == maxB)
        {
            ans.pb(maxA);
            a.erase(a.begin(), a.begin() + idxA + 1);
            b.erase(b.begin(), b.begin() + idxB + 1);
        }
        else if (maxA > maxB)
        {
            a.erase(a.begin() + idxA);
        }
        else
        {
            b.erase(b.begin() + idxB);
        }
    }

    cout << ans.size() << '\n';
    for (const int num : ans)
        cout << num << ' ';
}
