// URL: https://school.programmers.co.kr/learn/courses/30/lessons/42861
// Algo: MST 크루스칼

// Start:	240418 18 30
// Read:	0 1
// Think:	0 1
// Code:	0 10    폰 코딩
// Total:	0 12

#include <algorithm>
#include <vector>

using namespace std;

vector<int> p;

int Find(int n) {
    if (p[n] < 0) return n;
    return p[n] = Find(p[n]);
}

bool Union(int a, int b) {
    int ap = Find(a);
    int bp = Find(b);
    if (ap == bp) return false;
    
    if (-p[ap] < -p[bp]) swap(ap, bp);
    p[ap] += p[bp];
    p[bp] = ap;
    return true;
}

int solution(int n, vector<vector<int>> costs) {
    p.resize(n, -1);
    sort(costs.begin(), costs.end(), [](const auto& a, const auto& b) { return a[2] < b[2];});
    int answer = 0;
    int count = 0;
    
    for (const auto& cost : costs) {
      int a = cost[0];
      int b = cost[1];
      if (!Union(a, b)) continue;
        ++count;
        answer += cost[2];
       if (count == n - 1) break;
    }
    return answer;
}