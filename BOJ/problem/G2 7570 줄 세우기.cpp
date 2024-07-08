// URL: https://www.acmicpc.net/problem/7570
// Algo: DP, 그리디, LIS 변형

// Start:	240708 16 40
// Read:	0 2
// Think:	0 10
// Code:	0 4
// Total:	0 16

// 움직인 사람의 총 수를 최소로 만든다는 건, 움직이지 않는 사람들이 최대가 된다는 것인 LIS 문제의 변형임.
// 만약 움직이는 사람을 임의의 자리에 끼워넣을 수 있다면  전체 - LIS 가 최소 횟수가 되지만
// 이 문제처럼 맨 앞,뒤로만 옮길 수 있다면 조건이 달라짐
// 1 2 3 5 6 4  경우에서  4를 중간에 끼워넣기 위해서는 5,6을 뒤로 옮기는 2회가 필요하다
// 단순히 '증가'하는 수열이 아니라, '연속 증가'하는 최장 수열을 찾아야함 (1 2 3 4)

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    int n;
    cin >> n;

    int answer = -1;
    vector<int> idx(n + 1);
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        idx[num] = idx[num - 1] + 1;
        answer = max(answer, idx[num]);
    }

    cout << n - answer;
}
