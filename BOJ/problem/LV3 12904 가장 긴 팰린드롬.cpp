// URL: https://school.programmers.co.kr/learn/courses/30/lessons/12904
// Algo: 투 포인터 or DP

// Start:	240427 05 46
// Read:	0 1
// Think:	0 9
// Code:	0 25  s길이가 2인 엣지 케이스 못 찾고 헤맴
// Total:	0 35

// 와 회문! 투 포인터!로 풀릴 거 같았지만 그러면 레벨 3이 아닐거라고 생각해서 좀 고심해보니
// s[i] ~ s[j]가 회문이려면 무조건 s[i+1] ~ s[j-1]가 회문이어야 하는구나! 하고 DP로 풀었다. n이 2500이니 O(n^2)으로 가능.

// 그런데 다른 사람 풀이보니 투 포인터 풀이가 효율성 테스트에서 5ms->1ms로 5배 더 빠르다. 후...

// 지금까지 종종 나온 PS 풀이 방식대로, 중심축 mid를 맨왼쪽부터 오른쪽 끝까지 쭉 밀면서
// 중심축 좌우로 투 포인터 탐색을 하여, 중심축이 문자열 중간인 최대 길이의 회문을 찾는다.

// 이때 길이가 홀수, 짝수일 경우가 나뉘니 투포인터 인덱스를 i, i로도 돌리고, i, i+1로도 돌려야 함.
// 시간 복잡도는 똑같이 O(n^2)이지만 당연히 연산이 훨씬 더 적다.
// 이게 정해인 거 같음. 좀 더... 고심하고 문제 풀자


// 투 포인터 풀이
#include <string>
#include <algorithm>

using namespace std;

int Palin(const string& s, int left, int right) {
	while (left >= 0 && right < s.size())
    {
		if (s[left] != s[right]) break;
		--left;
		++right;
	}

	return right - left - 1;
}

int solution(string s)
{
    int answer = -1;
	for (int i = 0; i< s.size(); ++i)
    {
		answer = max(answer, Palin(s, i, i+1));
		answer = max(answer, Palin(s, i, i));
	}
	return answer;
}


/*
// DP 풀이
#include <string>
#include <vector>
using namespace std;
int solution(string s)
{
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size()));
    
    int answer = 1;
    for (int i = 0; i < s.size(); ++i)
    {
        dp[i][i] = true;
        if (s[i] == s[i+1])
        {
            dp[i][i+1] = true;
            answer = 2;
        }
    }
    
    for (int len = 3; len <= s.size(); ++len)
    {
        for (int i = 0, j = len - 1; i < s.size() - len + 1; ++i, ++j)
        {
            if (dp[i + 1][j - 1] && s[i] == s[j])
            {
                dp[i][j] = true;
                answer = len;
            }
        }
    }

    return answer;
}
*/