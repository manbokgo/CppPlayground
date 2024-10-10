// URL: https://www.acmicpc.net/problem/16566
// Algo: 분리 집합, 이분 탐색

// Start:	241011 06 50
// Read:	0 2
// Think:	0 12
// Code:	0 10
// Total:	0 24
// 오모시로이

// G2 10775 공항 문제와 비슷하다. x 초과인 수 중에 아직 사용되지 않은 가장 작은 숫자를
// 부모로 하는 집합을 만드는 분리 집합 문제다.

// 1) 540MB 512ms
// 간단한 풀이. n 크기의 p를 만들고, iota를 통해 다음 숫자를 부모로 둔 뒤, 뽑은 카드들만 p에 -1을 넣어
// 집합의 부모가 되도록 한다.

// 2) 332MB 692ms
// 문제 분류대로 이분 탐색까지 사용하는 풀이다. 숫자를 담고 있는 m 크기의 arr 배열을 만들고
// m 크기의 p의 값이 arr의 인덱스 을 의미하게 한다.
// upper_bound로 찾아낸 x 초과인 수에 Find를 하여 사용할 arr 인덱스를 알아내는 방식.

// 이때, arr이 4백만이나 되는만큼 정렬 비용도 크다.
// picked 배열을 따로 사용하여, 처음부터 arr에 순서대로 넣으면 정렬을 생략되므로 빨라진다 692ms -> 400ms

// 3) 181MB 768ms
// 약간 어이가 없지만, 쿼리 횟수 k가 최대 1만밖에 되지 않기 때문에 분리 집합을 아예 쓰지 않아도 된다.
// 2번 풀이에서 분리 집합만 뺀다. m 크기의 arr 배열과 used 사용 배열을 만든 후,
// upper_bound로 찾아낸 x 초과인 수에서부터 시작해, 사용되지 않은 가장 작은 수를 while 루프로 찾는다.


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int p[4'000'001];

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
    if (ap < bp) swap(ap, bp);

    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

// 풀이 1) 540MB 512ms
int main()
{
    fastio;

    int n, m, k;
    cin >> n >> m >> k;

    iota(p, p + n + 1, 1);

    while (m--)
    {
        int num;
        cin >> num;
        p[num] = -1;
    }

    while (k--)
    {
        int num;
        cin >> num;
        num = Find(num + 1);

        cout << num << '\n';
        Union(num, num + 1);
    }
}

// 풀이 2) 332MB 692ms
/*
vector<int> arr;
int main()
{
    fastio;
    memset(p, -1, sizeof(p));

    int n, m, k;
    cin >> n >> m >> k;

    arr.reserve(m);

    while (m--)
    {
        int num;
        cin >> num;
        arr.pb(num);
    }
    sort(all(arr));

    // 뽑은 카드들을 bool 배열로 체크한 후 앞에서부터 순서대로 넣어주면
    // arr을 정렬할 필요가 없어 더 빠르다. 692ms -> 400ms

    // vector<bool> picked(n + 1);
    // while (m--)
    // {
    //     int num;
    //     cin >> num;
    //     picked[num] = true;
    // }
    //
    // for (int i = 0; i < used.size(); ++i)
    // {
    //     if (picked[i]) arr.pb(i);
    // }


    while (k--)
    {
        int num;
        cin >> num;

        int idx = upper_bound(all(arr), num) - arr.begin();
        idx = Find(idx);
        cout << arr[idx] << '\n';

        Union(idx, idx + 1);
    }
}
*/

// 풀이 3) 181MB 768ms
/*
vector<int> arr;
vector<bool> used;
int main()
{
    fastio;

    int n, m, k;
    cin >> n >> m >> k;

    arr.reserve(m);
    used.resize(m);

    while (m--)
    {
        int num;
        cin >> num;
        arr.pb(num);
    }
    sort(all(arr));

    while (k--)
    {
        int num;
        cin >> num;

        int idx = upper_bound(all(arr), num) - arr.begin();
        while (used[idx])
        {
            ++idx;
        }

        used[idx] = true;
        cout << arr[idx] << '\n';
    }
}
*/
