// URL: https://www.acmicpc.net/problem/1208
// Algo: 밋 인 더 미들, 백트래킹 or 비트마스킹

// Start:	240531 02 05
// Read:	0 2
// Think:	0 34
// Code:	0 6
// Total:	0 42
// 오모시로이
// 패배

// 딱 봐도 모든 부분집합을 검사한다면 2^40으로 시간초과인데
// 어떻게 풀어야 하는지 오래 생각해봐도 모르겠어서 결국 해결법 찾아 봄

// 밋 인 더 미들이라는 테크닉을 사용하는 문제다
// 수열을 절반으로 나눠서 각각 부분집합을 검사해
// 왼쪽 2^20 + 오른쪽 2^20.  총 시간복잡도 2^21으로 가능해진다. 오...

// 처음에 초안 짤 때 비트마스킹으로 해서, 제출풀이도 비트마스킹으로 했는데 좀 깔끔하지 않다.
// 이 문제처럼 간단한 경우엔 모든 조합 검사로는 백트래킹 DFS가 더 깔끔한 듯.
// (물론 이렇게 단순히 선택/미선택이 아니라 G1 15683 감시 문제처럼
// 각 요소별 상태가 있는 경우(ex 카메라가 바라보는 방향) 4진법 비트마스킹을 사용하는 등 필요할 때가 있다)

// unordered_map을 사용하면 180ms 21MB 이지만 테케상 메모리를 엄청나게 잡아먹어서
// 6백만 크기의 배열을 써도 메모리는 거의 똑같다. 16ms 25MB

// pivotSum[target - sum + pivot] 코드를 예로 들어, target 1백만, sum -2백만이라면 3백만이니
// 배열 크기는 6백만으로 두고, 3백만 값을 피벗으로 초과면 양수, 미만이면 음수로 취급해야함

// 시간복잡도를 따지면 map은 '평균' O(1), 버킷 충돌시 최악 O(N)에다가 해시연산과 같은 비용이 크지만
// 배열은 심플하게 그냥 O(1)이니 훨씬 더 빠르다. 이렇게 확연히 드러나는 케이스는 처음 보는 듯


#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
using ll = long long;

int n, target;
int arr[40];
ll answer = 0; // 실수: 자료형 int면 오버플로 남

// unordered_map<int, int> leftSum;
// OR
int pivotSum[6'000'001];
constexpr int pivot = 3'000'000;


void Left(int pos, int sum)
{
    if (pos == n / 2)
    {
        // ++leftSum[sum];
        ++pivotSum[sum + pivot];
        return;
    }

    Left(pos + 1, sum);            // 미선택
    Left(pos + 1, sum + arr[pos]); // 선택
}

void Right(int pos, int sum)
{
    if (pos == n)
    {
        // if (leftSum.count(target - sum))
        //     answer += leftSum[target - sum];

        if (pivotSum[target - sum + pivot])
            answer += pivotSum[target - sum + pivot];
        return;
    }

    Right(pos + 1, sum);            // 미선택
    Right(pos + 1, sum + arr[pos]); // 선택
}


int main()
{
    fastio;
    cin >> n >> target;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    // 백트래킹
    Left(0, 0);
    Right(n / 2, 0);

    // 비트마스킹
    /*
    const int half = n / 2;
    for (ll mask = 0; mask < 1LL << half; ++mask)
    {
        int sum = 0;
        for (int i = 0; i < half; ++i)
        {
            if (mask & 1LL << i)
            {
                sum += arr[i];
            }
        }

        ++leftSum[sum];
    }

    const int rHalf = n - half;
    for (ll mask = 0; mask < 1LL << rHalf; ++mask)
    {
        int sum = 0;
        for (int i = 0; i < rHalf; ++i)
        {
            if (mask & 1LL << i)
            {
                sum += arr[i + half];
            }
        }

        if (leftSum.count(target - sum))
            answer += leftSum[target - sum];
    }
    */

    if (target == 0) --answer;
    cout << answer;
}
