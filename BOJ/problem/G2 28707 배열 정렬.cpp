// URL: https://www.acmicpc.net/problem/28707
// Algo: 다익스트라, 해시

// Start:	240618 12 06
// Read:	0 2
// Think:	0 21
// Code:	0 20
// Total:   0 43

// 플로이드 안 된다. 정렬 후의 최종 위치로 각 요소를 하나하나 움직이는 걸 생각해보았는데
// 최소 경로가 여러 개면 스왑된 후의 상태가 가지각색이어서 어떤게 최적인지 판단할 수 없을 뿐더러
// 어떤 요소를 먼저 움직이냐에 따라 최적인지가 또 달라짐. 이건 아닌가 싶다.

// '배열의 상태'를 일종의 노드로 보는 방식으로 접근하면 될 듯   

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

using tiii = tuple<int, int, int>;
using piv = pair<int, vector<int>>;

// template <>
// struct std::hash<vector<int>>
// {
//     std::size_t operator()(const vector<int>& V) const noexcept
//     {
//         int hash = V.size();
//         for (const int i : V) hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//         return hash;
//     }
// };

int MakeHash(const vector<int>& v)
{
    int hash = 0;
    int mul = 1;
    for (const int i : v)
    {
        hash += i * mul;
        mul *= 10;
    }
    return hash;
}

int main()
{
    fastio;

    int n, m;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cin >> m;

    vector<tiii> adj(m);
    for (int i = 0; i < m; ++i)
    {
        auto& [a,b,c] = adj[i];
        cin >> a >> b >> c;
        --a;
        --b;
    }

    unordered_map<int, int> um;
    // unordered_map<vector<int>, int> um;
    priority_queue<piv, vector<piv>, greater<>> pq;

    int arrHash = MakeHash(arr);
    um[arrHash] = 0;
    pq.push({um[arrHash], arr});

    while (!pq.empty())
    {
        auto [cost, vec] = std::move(const_cast<piv&>(pq.top()));
        pq.pop();

        if (cost != um[MakeHash(vec)]) continue;
        for (const auto& [a, b, c] : adj)
        {
            swap(vec[a], vec[b]);
            const int hash = MakeHash(vec);
            if (!um.count(hash) || um[hash] > cost + c)
            {
                um[hash] = cost + c;
                pq.push({um[hash], vec});
            }
            swap(vec[a], vec[b]);
        }
    }

    sort(all(arr));
    arrHash = MakeHash(arr);
    if (um.count(arrHash)) cout << um[arrHash];
    else cout << -1;
}
