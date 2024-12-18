// URL: https://www.acmicpc.net/problem/2261
// Algo: 분할 정복 or 스위핑

// Start:	241219 04 20
// Read:	0 1
// Think:	0 42
// Code:	0 49
// Total:   1 32

// Closest Pair 알고리즘
// https://blog.naver.com/babobigi/220530321348

// 분할 정복 방식, 스위핑 방식 둘 다 아주 깔끔하게 잘 정리한 블로그
// https://st-lab.tistory.com/256
// https://casterian.net/ps/boj2261/

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back
#define X first
#define Y second

using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

pii p[100'000];

int Square(int a) { return a * a; }
int GetDistSquare(pii a, pii b) { return Square(a.X - b.X) + Square(a.Y - b.Y); }

int Solve(int st, int en)
{
    // en-st+1 (size) 가 2, 3일 때 최소 거리를 계산해 return 해줘야 한다
    // 좀 비효율적이긴 하지만 그냥 size 1일 때 INF를 반환하기만 하면
    // 2, 3일 때 아래 로직이 돌면서 알아서 최소 거리 구해져서 간단함
    // if (en - st + 1 == 1) return INF;

    if (en - st + 1 == 2) return GetDistSquare(p[st], p[st + 1]);
    if (en - st + 1 == 3)
        return min({
            GetDistSquare(p[st], p[st + 1]), GetDistSquare(p[st], p[st + 2]), GetDistSquare(p[st + 1], p[st + 2])
        });

    const int mid = (st + en) / 2;
    int dist = min(Solve(st, mid), Solve(mid + 1, en));

    vector<pii> candi;
    for (int i = st; i <= en; ++i)
    {
        if (Square(p[i].X - p[mid].X) <= dist)
            candi.pb(p[i]);
    }

    sort(all(candi), [](pii a, pii b)
    {
        if (a.Y != b.Y) return a.Y < b.Y;
        return a.X < b.X;
    });

    for (int i = 0; i < candi.size(); ++i)
    {
        for (int j = i + 1; j < candi.size(); ++j)
        {
            if (Square(candi[j].Y - candi[i].Y) >= dist) break; // 등호 없으면 저격 케이스 때문에 시간 초과
            dist = min(dist, GetDistSquare(candi[i], candi[j]));
        }
    }
    return dist;
}

int main()
{
    fastio;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> p[i].X >> p[i].Y;

    sort(p, p + n);

    // 분할 정복 4976KB 60ms
    cout << Solve(0, n - 1);
    return 0;

    // 스위핑 3876KB 52ms
    auto cmp = [](pii a, pii b)
    {
        if (a.Y != b.Y) return a.Y < b.Y;
        return a.X < b.X;
    };

    set<pii, decltype(cmp)> candi(cmp);
    candi.insert(p[0]);
    candi.insert(p[1]);

    int minDist = GetDistSquare(p[0], p[1]);
    int idx = 0;
    for (int pivot = 2; pivot < n; ++pivot)
    {
        while (idx < pivot) 
        {
            if (Square(p[pivot].X - p[idx].X) <= minDist) break;
            candi.erase(p[idx]);
            ++idx;
        }

        const int realDist = (int)sqrt(minDist);
        const auto st = candi.lower_bound({-INF, p[pivot].Y - realDist}); // 좌측 하단
        const auto en = candi.upper_bound({INF, p[pivot].Y + realDist});  // 우측 상단
        for (auto it = st; it != en; ++it)
            minDist = min(minDist, GetDistSquare(p[pivot], *it));

        candi.insert(p[pivot]);
    }

    cout << minDist;
}
