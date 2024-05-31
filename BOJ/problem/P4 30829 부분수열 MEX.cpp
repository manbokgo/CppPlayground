// URL: https://www.acmicpc.net/problem/30829
// Algo: 애드 혹 or DP

// Start:	240601 00 10
// Read:	0 2
// Think:	3 0
// Code:	0 34
// Total:	3 36

// 접근법은 30분만에 캐치했는데 40%에서 계속 틀림. 반례 안 떠올라서 미치는 줄 알았다
// 맞힌사람 20명짜리 문제라서 포기하고 해설보려고 해도 아무 것도 안 나옴. 아 ㅋㅋ

// 0~9가 하나 이상씩 포함되어 있는 묶음으로 구간을 나누고 pos, 맨앞쪽에서 1~9 중 빠지는 숫자를
// 이전 구간에서 찾고, 구간 내 오른쪽에서 0~9 중 빠진 숫자를 찾는 걸 반복하는 식이다.
// 구간의 정의에 따라 구간 내 오른쪽에서는 반드시 숫자 하나 이상은 빠져있게 된다.
// 암만 생각해도 이 방식이 틀린 건 같지 않은데 새벽에 3시간 내내 맞왜틀 외침

// 드디어 드디어 생각해낸 반례 123456789 23456789001  output 100  answer 102
// 위처럼 맨앞이 0만 빠진 묶음으로 끝나게 되면 00~99를 만들 수 있으니 그냥 100이 답이네! 하고 멍청하게 생각했다.
// 이렇게 뒤에서 0이 중복으로 나오는 경우 100도 가능하고 나열된 순서에 따라 101, 102 등등도 가능함
// 맨앞이 0만 빠진 묶음이면 1로 시작하고 이전 구간에서 0을 찾는 식으로 바꿔서 정답

// 그래도 내가 푼 방식이 지금 해결풀이 중에서는 가장 효율적인 듯 하다... 4ms 2.5MB
// 다른 사람들 풀이는 dp 방식으로 하는데 가장 나은 것도 8ms 5MB임 하하!

// dp 방식도 내가 한 것과 로직은 비슷하다.
// 난 구간 내를 순회하면서 숫자를 찾는데, dp는 미리 다음 위치 숫자를 저장해놓는 방식임

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    string str;
    cin >> str;
    const int n = str.size();

    int pos[20'005]{};
    pos[0] = n;
    int now = 1;

    int remain = 10;
    bool checked[10]{};

    for (int i = n - 1; i >= 0; --i)
    {
        const int num = str[i] - '0';
        if (!checked[num])
        {
            --remain;

            if (remain == 0)
            {
                remain = 10;
                memset(checked, false, sizeof(checked));
                pos[now++] = i;
            }
            else
            {
                checked[num] = true;
            }
        }
    }
    pos[now] = 0;

    vector<int> answer;
    answer.reserve(now);

    int findNum = 1;
    for (int i = 1; i < 10; ++i)
    {
        if (!checked[i])
        {
            answer.pb(i);
            findNum = i;
            break;
        }
    }
    if (answer.empty()) answer.pb(findNum);

    do
    {
        for (int i = pos[now]; i < pos[now - 1]; ++i)
        {
            if (str[i] - '0' == findNum)
            {
                memset(checked, false, sizeof(checked));
                for (int j = i + 1; j < pos[now - 1]; ++j)
                    checked[str[j] - '0'] = true;

                for (int j = 0; j < 10; ++j)
                {
                    if (!checked[j])
                    {
                        answer.pb(j);
                        findNum = j;
                        break;
                    }
                }
                break;
            }
        }
    } while(--now);

    for (const int num : answer) cout << num;
}
