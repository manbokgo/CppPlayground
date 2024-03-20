// URL: https://www.acmicpc.net/problem/19942
// Algo: 브루트포스(부분집합 비트마스킹)

// Start:	240313 02 28
// Read:	0 1
// Think:	0 1     N이 15면 부분집합 O(2^N)의 모든 경우로 풀면 되겠네
// Code:	0 26    정답 집합 중에 사전순으로 가장 빠른 것만 출력해야하는 거에 실수 많이 함
// Total:	0 28

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

struct nutrient
{
    int p;
    int f;
    int s;
    int v;
    int c;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, mp, mf, ms, mv;
    cin >> n >> mp >> mf >> ms >> mv;

    vector<nutrient> ings(n);
    for (int i = 0; i < n; ++i)
    {
        int p, f, s, v, c;
        cin >> p >> f >> s >> v >> c;
        ings[i] = {p, f, s, v, c};
    }

    int         answerCost = INF;
    vector<int> answerIngs;
    vector<int> curIngs;

    for (int bits = 1; bits < 1 << n; ++bits)
    {
        nutrient sum{};
        for (int j = 0; j < n; ++j)
        {
            if (bits & 1 << j)
            {
                sum.p += ings[j].p;
                sum.f += ings[j].f;
                sum.s += ings[j].s;
                sum.v += ings[j].v;
                sum.c += ings[j].c;
            }
        }

        if (sum.p >= mp &&
            sum.f >= mf &&
            sum.s >= ms &&
            sum.v >= mv)
        {
            if (sum.c <= answerCost)
            {
                curIngs.clear();
                for (int j = 0; j < n; ++j)
                {
                    if (bits & 1 << j)
                    {
                        curIngs.pb(j + 1);
                    }
                }

                if (sum.c < answerCost || answerIngs > curIngs)
                    answerIngs = curIngs;

                answerCost = sum.c;
            }
        }
    }

    if (answerCost == INF)
    {
        cout << -1;
    }
    else
    {
        cout << answerCost << "\n";
        for (int num : answerIngs)
        {
            cout << num << " ";
        }
    }
}
