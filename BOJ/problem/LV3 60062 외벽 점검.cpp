// URL: https://school.programmers.co.kr/learn/courses/30/lessons/60062
// Algo: 순열, 완전 탐색

// Start:	240504 23 40
// Read:	0 2
// Think:	0 17
// Code:	0 16
// Total:	0 35

// 완전탐색으로는 시간 복잡도가 안 될거 같다고 (잘못) 생각해서 처음엔 그리디로 생각해봄
// 반례 계속 떠오르는거 보고 너무 복잡해져서 아닌갑다하고 다시 살펴보니
// O(8!) 시간복잡도로 충분히 가능하니 완전 탐색이 맞다고 깨달음

// x->y로 시계 방향으로 가는 것과,  y->x 반시계 방향으로 가는 것은 동일한 탐색이니 완전 탐색이면 시계 방향만 하면 된다.

// 원점을 지난 경우를 확인하는게 까다로운데, 단순한 경우라면 인덱스 % n 으로 올바른 인덱스를 구할 수 있겠지만
// 이 문제처럼 복잡한 경우엔, 마지막 요소를 제외한 모든 요소에 n을 더한 더미 weak들을 추가해주면 깔끔하다

#include <algorithm>
#include <vector>

using namespace std;
constexpr int INF = 0x3f3f3f3f;

int solution(int n, vector<int> weak, vector<int> dist) {
    int wSz = weak.size();
    for (int i = 0; i < wSz - 1; ++i)
        weak.push_back(weak[i] + n);
    
    sort(dist.begin(), dist.end());
    
    int answer = INF;
    do {
        for (int st = 0; st < wSz; ++st)
        {
            int en = st + wSz - 1;
            int cur = st;
            for (int i = 0; i < dist.size(); ++i)
            {
                if (weak[cur] + dist[i] >= weak[en]) {
                    answer = min(answer, i + 1);
                    break;
                }
                
                for (int j = cur + 1; j <= en; ++j)
                {
                    if (weak[cur] + dist[i] < weak[j]) {
                        cur = j;
                        break;
                    }
                }
            }
        }
    } while (next_permutation(dist.begin(), dist.end()));
    
    return answer != INF ? answer : -1;
}