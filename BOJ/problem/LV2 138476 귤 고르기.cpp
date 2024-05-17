// URL: https://school.programmers.co.kr/learn/courses/30/lessons/138476
// Algo: 구현

// Start:	240517 14 06
// Read:	0 2
// Think:	0 1
// Code:	0 6
// Total:	0 9

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

using pii = pair<int, int>;

int solution(int k, vector<int> tangerine)
{
    unordered_map<int, int> M;
    for (const int tan : tangerine)
        ++M[tan];

    vector<pii> V(M.begin(), M.end());
    sort(V.begin(), V.end(), [](const pii a, const pii b) { return a.second > b.second; });
    for (int i = 0; i < V.size(); ++i)
    {
        k -= V[i].second;
        if (k <= 0) return i + 1;
    }

    return -1;
}
