// URL: https://www.acmicpc.net/problem/17609
// Algo: 투 포인터

// 반례 생각하기가 힘들어서 헤맸음. xabba 경우만 보곤 왼쪽, 오른쪽 중
// 어느 쪽 글자를 지워야하는지 명확하다고 생각해서 원패스로 했는데 틀림.
// xaaxa 경우 왼쪽 먼저 지우면 당장 진행은 되지만 회문 아니라고 판별됨.
// 이 경우 오른쪽 지우는 패스를 한번 더 해서 회문인지 재차 검사를 해야함.

// Start:	240215 05 41
// Read:	05 41
// Think:	05 43
// Code:	06 25
// Total:	0 44

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string text;
    while (n--)
    {
        cin >> text;

        int st = 0;
        int en = text.size() - 1;
        int result = 0;

        // 회문이면 더 진행할 필요 없음
        // 아니라면 일단 커서 멈춤
        for (; st <= en; ++st, --en)
        {
            if (text[st] != text[en])
            {
                result = 1;
                break;
            }
        }

        // 멈춘 커서에서 왼쪽 한칸만 움직여서
        // 왼쪽 한 글자 지우고 진행하면 회문이 되는지 검사
        if (result == 1)
        {
            int st2 = st + 1;
            int en2 = en;
            for (; st2 <= en2; ++st2, --en2)
            {
                if (text[st2] != text[en2])
                {
                    result = 2;
                    break;
                }
            }
        }

        // 왼쪽 한 글자 지워도 회문이 아니라면,
        // 이번엔 멈춘 커서에서 오른쪽 한칸만 움직여서
        // 오른쪽 한 글자 지우고 진행하면 회문이 되는지 검사
        if (result == 2)
        {
            int st2 = st;
            int en2 = en - 1;
            for (; st2 <= en2; ++st2, --en2)
            {
                if (text[st2] != text[en2])
                {
                    result = 2;
                    break;
                }
            }

            if (st2 > en2) result = 1;
        }

        // 출력
        cout << result << "\n";
    }
}
