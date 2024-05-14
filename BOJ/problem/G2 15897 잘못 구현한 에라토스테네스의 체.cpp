// URL: https://www.acmicpc.net/problem/15897
// Algo: 수학, 정수론

// Start:	240513 22 07
// Read:	0 2
// Think:	0 17
// Code:	0 7
// Total:	0 26

// 정수론 문제에서 유명한 문제 유형 Harmonic-Lemma 문제. 시간 복잡도 O(루트N)
// 이름에 조화(Harmonic)가 들어있긴 하지만, 단순히 각 항의 역수가 등차순열인 조화수열(1/1 1/2 1/3...)에 대한 게 아니라
// 수열의 각 항이 [n/i], 'n을 i로 나눈 몫'인 수열을 의미한다.
// 같은 값을 가지는 항들의 구간을 구해서, 그 값만큼 곱한 것들의 총합이 정답이다.

// [n/x] = k 에서 x의 최대 실수값은 n/k이다. 즉 x의 최대 정수는 [n/k]이다.
// 따라서 동일 값 구간 [n/i] ~ [n/j] 에서 j는 [n / [n/i]] 임을 이용하여 구간을 찾는다.

// https://xy-plane.tistory.com/17
// https://ahgus89.github.io/algorithm/Harmonic-Lemma/

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
using ll = long long;

// 정해 Harmonic-Lemma + sqrt(n) 인덱스까지는 나이브하게 하기
int main()
{
    fastio;

    ll n;
    cin >> n;
    if (n == 1)
    {
        cout << 1;
        return 0;
    }

    ll answer = n + 1; // i 1, n에서 각각의 답 n, 1임

    ll sqt = sqrt(n - 1);
    for (int i = 2; i <= sqt; ++i)
        answer += ((n - 1) / i + 1);

    for (ll i = sqt + 1, j; i < n; i = j + 1)
    {
        j = (n - 1) / ((n - 1) / i);
        answer += ((n - 1) / i + 1) * (j - i + 1);
    }

    cout << answer;
}


/*
// 정해 Harmonic-Lemma
int main()
{
    fastio;

    ll n;
    cin >> n;
    if (n == 1)
    {
        cout << 1;
        return 0;
    }

    ll answer = n + 1; // i 1, n에서 각각의 답 n, 1임

    for (ll i = 2, j; i < n; i = j + 1)
    {
        j = (n-1) / ( (n-1) / i);
        answer += ( (n-1) / i + 1) * (j - i + 1);
    }

    cout << answer;
}
*/

/*
// 제출 풀이. 정해와 비교하면 여기서 i가 의미하는 바는 (n-1)/인덱스 임
// (n-1)/인덱스 가 작은 순에서 큰 순으로 순회하며
// 인덱스 맨뒤에서부터 앞으로 이동하며 구간을 찾는 방식.
int main()
{
    fastio;

    ll n;
    cin >> n;

    ll answer = 0;
    ll lst = n;
    for (ll i = 1; i <= n;)
    {
        ll tmp = (n - 1) / i;
        answer += (lst - tmp) * i;
        if (tmp == 0) break;

        lst = tmp;
        ll md = (n-1) % i;
        i += md / tmp + 1;
    }

    cout << answer;
}
*/
