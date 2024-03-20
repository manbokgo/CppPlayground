// URL: https://www.acmicpc.net/problem/13144
// Algo: 투 포인터

// Start:	240318 22 34
// Read:	0 0
// Think:	0 2
// Code:	0 26    테케 다 받는데 왜 오답임?
// Code:	0 34    최악 경우를 생각하면 answer 타입이 int가 아니라 ll이었어야함 아 ㅋㅋ
// Total:	1 2

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

int n;
int nums[100'001];
bool visited[100'001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    ll answer = 0;
    for (int st = 0, en = 0; st < n; ++st)
    {
        while (en < n && !visited[nums[en]])
        {
            visited[nums[en]] = true;
            ++en;
        }

		answer += en - st;
		visited[nums[st]] = false;
    }

    cout << answer;
}
