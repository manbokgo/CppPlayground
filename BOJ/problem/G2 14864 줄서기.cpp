﻿// URL: https://www.acmicpc.net/problem/14864
// Algo: 애드 혹

// Start:	240912 17 00
// Read:	0 3
// Think:	0 41
// Code:	0 4
// Total:	0 48
// 오모시로이

// 가장 먼저 생각한 건 자신 기준 앞 구간의 큰 숫자와 뒷 구간의 작은 숫자의 개수를 고려해서
// 등수를 매기는 것이었는데 시간 복잡도가 안 될 거라고 생각해서 넘겼으나...
// 다 푼 후에 보니 m이 100만으로 한정되어 있으니 충분히 가능한 방식이었다. 멍청함.

// 1~n까지 빈칸이 있다고 했을 때, 'a로 시작하는 쌍의 개수만큼' 밑에서부터 세서 차지하는 식으로 생각했다.
// (단, 이미 차지된 칸은 건너뛰면서 센다)
// 1로 시작하는 쌍이 2개라면 학생1은 3카드라는 방식.

// 논리적으로 가능한 방식이기는 한데 '맨 밑에서 9만 번째로 가능한 칸' 같은 걸 생각해보니 말이 안 된다.
// 처음부터 쭉 순회하면서 칸을 세야하기 때문에 최악의 경우 10만을 다 순회하니, 10만x10만 = 100억으로 시간 복잡도가 안 됨.
// 무엇보다도 이건 b의 정보를 아예 안 쓰는 방식이라서 아닐 거 같았음.

// b까지 써먹는 방법을 곰곰히 생각해보니, 쌍에서 a가 나올 때마다 ++을 한다면 b는 --를 해야하지 않나 짐작함.

// 아래와 같은 경우를 가정해보니 명확해짐
// 1 2 3  X
// 3 1 2  (1,2) (1,3)
// 3 2 1  (1,2) (1,3) (2,3)

// 1 2 3 4  X
// 4 2 3 1  (1,2) (1,3) (1,4) (2,4) (3,4)

// 처음엔 1 2 3 4... 자기 인덱스대로 숫자를 가지고 위 방식대로 ++, --를 하면 최종 숫자가 나옴.
// 말이 안 되는 입력이라면 최종 숫자가 중복이 나오므로 검사 가능
// (참고로 이것도 m이 100만이라는 한정이 없으면 안 되는 방식이다.)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int num[100'001];
bool inUse[100'001];

int main()
{
    fastio;

    int n, m;
    cin >> n >> m;

    iota(num + 1, num + n + 1, 1);
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        ++num[a];
        --num[b];
    }

    for (int i = 1; i <= n; ++i)
    {
        if (inUse[num[i]])
        {
            cout << -1;
            return 0;
        }

        inUse[num[i]] = true;
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << num[i] << ' ';
    }
}
