// URL: https://www.acmicpc.net/problem/10775
// Algo: 그리디, 분리 집합 or 해시 맵 or 매개변수 탐색

// Start:	240914 14 03
// Read:	0 2
// Think:	0 5
// Code:	0 10
// Total:	0 17
// 오모시로이

// 'x 이하의 숫자 중 사용되지 않은 가장 큰 숫자'를 찾는 게 핵심인 문제.
// 분리 집합 접근이 신박했다. 지식이 늘었다.

// 1. 가능한 숫자가 들어있는 greater<> set를 lower_bound하여, x 이하 중 가장 큰 것을 찾아 지운다.
// 유의: 해시 맵(map, set 등)은 선형 구조가 아닌만큼 std::lower_bound를 사용한다면 선형 탐색을 한다.
// 트리 구조에 알맞게 짜여진 std::set::lower_bound를 사용해야 함.

// 2. 분리 집합 풀이
// x 이하인 수 중에 아직 사용되지 않은 가장 큰 숫자를 부모로 하는 집합을 만든다.
// [1~9] 범위에서 2, 4, 6, 7, 8이 제거된 상태는 {1, 2}, {3, 4}, {5, 6, 7, 8}, {9} 으로 집합을 나눌 수 있다.
// 두 집합을 Union할 때는 작은 숫자가 부모가 되도록 한다. 만약 숫자 a를 사용했다면 a 집합과 a-1 집합을 Union한다.

// 예를 들어 x로 8이 들어온다면, 8의 부모인 5를 사용하게 된다.
// 이후 5와 4를 Union하면 {5, 6, 7, 8}의 최종 부모가 3이 된다.

// 3. 매개변수 탐색(이분 탐색) 풀이
// 1~mid번 비행기만을 배치한 후, i번째 게이트까지의 비행기 총합이 i 초과라면 불가능하다고 판단한다.


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int p[100'001];

int Find(int a)
{
    if (p[a] < 0) return a;
    return p[a] = Find(p[a]);
}

// 변형
bool Union(int a, int b)
{
    int ap = Find(a);
    int bp = Find(b);

    if (ap == bp) return false;
    // if (-p[ap] < -p[bp]) swap(ap, bp);
    if (ap > bp) swap(ap, bp);

    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}


int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    // 분리 집합 풀이
    memset(p, -1, sizeof(p));

    int answer = 0;
    while (m--)
    {
        int num;
        cin >> num;

        num = Find(num);
        if (num == 0) break;

        Union(num, num - 1);
        ++answer;
    }
    cout << answer;


    // 해시 맵 Set 풀이
    /*
    set<int, greater<>> S;
    for (int i = 1; i <= n; ++i) S.insert(i);

    int answer = 0;
    while (m--)
    {
        int num;
        cin >> num;

        const auto it = S.lower_bound(num);
        if (it == S.end()) break;

        S.erase(it);
        ++answer;
    }
    cout << answer;
    */


    // 매개변수 탐색 풀이 (귀찮으니깐 p 배열 그대로 사용)
    /*
    for (int i = 1; i <= m; ++i)
        cin >> p[i];

    int cnt[100'001];

    int lo = 0;
    int hi = n;
    while (lo < hi)
    {
        const int mid = (lo + hi + 1) / 2;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= mid; ++i)
            ++cnt[p[i]];

        bool success = true;
        for (int i = 1; i <= n; ++i)
        {
            cnt[i] += cnt[i-1];
            if (cnt[i] > i)
            {
                success = false;
                break;
            }
        }

        if (success) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
    */
}
