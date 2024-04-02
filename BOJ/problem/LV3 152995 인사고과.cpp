// URL: https://school.programmers.co.kr/learn/courses/30/lessons/152995
// Algo: 구현

// Start:	240402 18 02
// Read:	0 1
// Think:	0 2
// Code:	0 15 일부 테케 실패.
// Code:	0 25 또 실패. minA와 minB을 대상으로만 비교하는게 잘못됐다.
// Code:	0 17
// Total:	1 0
// 오모시로이

// '동석차의 수만큼 다음 석차는 건너 뛴다'
// 예를 들어 5점짜리 3명, 4점짜리 1명, 3점짜리 7명(+타겟)이 있으면 타겟의 등수는 5등.
// 핵심은 (살아남은 것들 중) 합이 타겟의 합보다 큰 것들의 개수를 세는 것이다.

// 처음 풀이 방식:
// a 오름차순해서 살아남는 것 중에 a가 가장 작은 것(minA)과 
// b 오름차순해서 살아남는 것 중에 b가 가장 작은 것(minB)을 찾고
// 타겟보다 합이 큰 것들 중에 minA와 minB와 비교해 살아남는 것들을 찾는 식으로 구현함

// 예시 테스트케이스에서는 통과했지만 채점에서는 테케 절반 정도는 틀렸는데
// 다시 생각해보니 {1, 999}, {999, 1}, {2, 2}, {3, 3} 와 같은 경우에서
// {2, 2}는 {3, 3}에 의해 죽어야하지만, minA {1, 999}와 minB {999, 1}와만 비교하면 살아남는다.
// 접근이 애초에 잘못됐음. minA minB 같은 특정 대상과만 비교하는게 아니라 가능한 비교 대상들을 모두 고려해야함.

// 깨달음: 내가 죽으려면 최소한 비교 대상이 내 합보다 커야한다.
// 제출 풀이 방식:
// 타겟보다 합이 큰 것들만 뽑아서 내림차순으로 정렬하고, 앞부터 순회하며 나보다 합이 큰 것과 모두 비교해 살아남으면 세주기.
// 특정 테케에서 300ms 이상 나오는 걸 보고 정해는 아니라고 생각 듦. 찾아보니 정말 간단하게 풀 수 있는 문제였다

// 정해 아이디어: 동일한 a값이라면 b의 대소는 무관하게 살아남고, 더 작은 a값이라면 b가 이전의 maxB보다 커야지 살아남을 수 있다.
// a기준 내림차순 -> b기준 오름차순 으로 pii를 정렬하고 앞에서부터 순회하며 살아남은 것 중 타겟합보다 합이 더 큰 것들만 세주면 된다

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;


// 아주 깔끔한 코드. 모든 테케 <20ms.
int solution(vector<vector<int>> scores) {
    auto target = scores[0];
    sort(scores.begin(), scores.end(), [](const auto& a, const auto& b)
    {
       return a[0] != b[0] ? a[0] > b[0] : a[1] < b[1];
    });

    int answer = 1;
    int maxB = -1;
    for (const auto& score : scores)
    {
        if (target[0] < score[0] && target[1] < score[1])
            return -1;

        if (score[1] < maxB) continue;

        maxB = score[1];
        if (score[0] + score[1] > target[0] + target[1])
            ++answer;
    }

    return answer;
}


// 제출된 코드. 특정 테케에서 300ms로 비효적임
/*
int solution(vector<vector<int>> scores) {
    int targetSum = scores[0][0] + scores[0][1];
    
    vector<pii> sums;
    sums.reserve(scores.size());
    for (int i = 1; i < scores.size(); ++i)
    {
        int sum = scores[i][0] + scores[i][1];
        if (sum > targetSum)
            sums.push_back({sum, i});
    }
    sort(sums.begin(), sums.end(), greater<>());
    
    int answer = 1;
    for (int i = 0; i < sums.size(); ++i)
    {
        auto [sum, idx] = sums[i];
        int a = scores[idx][0];
        int b = scores[idx][1];
        
        if (scores[0][0] < a && scores[0][1] < b)
            return -1;
        
        bool noInsen = false;
        for (int j = 0; j < i; ++j)
        {
            auto [nsum, nidx] = sums[j];
            int na = scores[nidx][0];
            int nb = scores[nidx][1];
            if (a < na && b < nb)
            {
                noInsen = true;
                break;
            }
        }
        
        if (!noInsen) ++answer;
    }
    
    return answer;
}
*/

int main()
{
    cout << solution({{2,2},{1,4},{3,2},{3,2},{2,1}});
}