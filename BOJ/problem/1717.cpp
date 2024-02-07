// URL: https://www.acmicpc.net/problem/1717
// Algo: 유니온파인드 기본 + Union by Size

// Start:	240208 01 00
// Read:	01 00
// Think:	01 00
// Code:	01 20
// Total:	0 20

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))
#define compress(x) x.erase(unique(all(x)), x.end())
#define findvec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr ll  MOD = 1000000007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll  LLINF = 1e18;

// 음수면 트리의 크기, 양수면 부모 노드
int p[1'000'001];

int Find(int a)
{
    if (p[a] < 0) return a; // 실수: a가 아니라 p[a] 반환했음. 바봉가?
    p[a] = Find(p[a]); // 경로 압축
    return p[a];
}

void MergeBySize(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);
    if (ap == bp) return;

    // 큰 ap의 아래로 작은 bp 넣기이므로
    // ap의 크기가 bp의 크기보다 크게하도록 스왑
    if (-p[ap] < -p[bp]) swap(ap, bp);
    p[ap] += p[bp];

    p[bp] = ap;
}

void MergeNaive(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);
    if (ap == bp) return;
    p[bp] = ap;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    memset(p, -1, sizeof(p));

    while (m--)
    {
        int func, a, b;
        cin >> func >> a >> b;

        if (func == 0)
        {
            MergeBySize(a, b);
        }
        else
        {
            int ap = Find(a);
            int bp = Find(b);

            if (ap == bp)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
}
