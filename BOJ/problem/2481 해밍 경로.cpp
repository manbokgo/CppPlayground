// URL: https://www.acmicpc.net/problem/2481
// Algo: BFS, 이분 탐색

// Start:	240318 03 22
// Read:	0 1
// Think:	0 2
// Code:	0 28
// Total:	0 31

// 이분탐색 풀이 O(kn log n)로는 메모리 3860 KB, 240ms
// 탐색이 잦은 상황이므로 unordered_map으로 탐색을 O(1)으로 줄이면
// O(kn log n)인건 같지만 메모리 7600KB, 176ms로 메모리 더 쓰고 시간 단축 가능

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int st = 1;

    int n, k;
    cin >> n >> k;

    vector<pii> nums(n + 1); // {num, idx}

    vector<bool> visit(n + 1);
    vector<int> pre(n + 1, INF);
    for (int i = 1; i <= n; ++i)
    {
        string num;
        cin >> num;

        nums[i] = {stoi(num, nullptr, 2), i};
    }

    queue<pii> q;
    q.push(nums[st]);
    visit[st] = true;

    SortVec(nums);
    while (!q.empty())
    {
        auto [num, idx] = q.front();
        q.pop();

        for (int i = 0; i < k; ++i)
        {
            int findNum = num ^ 1 << i;
            auto it = lower_bound(nums.begin() + 1, nums.end(), pii{findNum, 0});
            if (it != nums.end() && it->first == findNum)
            {
                auto [nNum, nIdx] = *it;
                if (visit[nIdx]) continue;
                visit[nIdx] = true;
                pre[nIdx] = idx;
                q.push(*it);
            }
        }
    }

    int m;
    cin >> m;
    vector<int> path;
    path.reserve(n);
    while (m--)
    {
        path.clear();

        int cur;
        cin >> cur;

        bool bFind = true;
        while (cur != st)
        {
            if (pre[cur] == INF)
            {
                bFind = false;
                break;
            }

            path.pb(cur);
            cur = pre[cur];
        }

        if (!bFind)
        {
            cout << -1 << '\n';
            continue;
        }

        path.pb(cur);
        reverse(all(path));
        for (auto num : path) cout << num << ' ';
        cout << '\n';
    }
}
