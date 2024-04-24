// URL: https://school.programmers.co.kr/learn/courses/30/lessons/42892
// Algo: 트리, DFS

// Start:	240424 18 21
// Read:	0 2
// Think:	0 4
// Code:	0 17
// Total:	0 23

// 완전 이진 트리였다면 right = i*2 와 같은 쌈뽕하게 했겠지만, 완전 이진 트리가 아니라서
// 자식을 어떻게 적절히 넣어주냐가 핵심임. 좀 생각해보니 문제 조건을 고려할 때
// 그냥 루트에서부터 타고 내려가다가 빈 자리에 들어가면 된다는 점 깨달음.

// 처음엔 좌표 정보는 ninfo 배열에 들은 걸 그대로 이용하도록 짰는데
// 맨처음 입력 배열의 인덱스를 보존해야 된다는 걸 뒤늦게 깨달아서
// 결국 Node 구조체에 인덱스랑 좌표까지 넣는 평이한 방식이 됨

#include <algorithm>
#include <vector>

using namespace std;

struct Node
{
    int idx;
    int x;
    int y;
    int l = -1;
    int r = -1;
};

vector<vector<int>> solution(vector<vector<int>> ninfo) {
    int n = ninfo.size();
    
    vector<Node> nodes;
    nodes.reserve(n);
    for (int i = 0; i < n; ++i)
        nodes.push_back({i+1, ninfo[i][0], ninfo[i][1]});
    
    sort(nodes.begin(), nodes.end(), [](const auto& a, const auto& b) { 
        return a.y != b.y ? a.y > b.y : a.x < b.x; });
   
    auto MAKE = [&](const auto& func, int p, int c) {
        if (nodes[c].x < nodes[p].x) {
            if (nodes[p].l == -1) {
                nodes[p].l = c;
                return;
            }
            func(func, nodes[p].l, c);
        }
        else {
            if (nodes[p].r == -1) {
                nodes[p].r = c;
                return;
            }
            func(func, nodes[p].r, c);
        }
    };
    
    for (int i = 1; i < n; ++i)
        MAKE(MAKE, 0, i);
    
    
    
    vector<vector<int>> answer(2);
    
    auto PRE = [&](const auto& func, int node) {
        if (node == -1) return;
        answer[0].push_back(nodes[node].idx);
        func(func, nodes[node].l);
        func(func, nodes[node].r);
    };
    PRE(PRE, 0);
    
    auto POST = [&](const auto& func, int node) {
        if (node == -1) return;
        func(func, nodes[node].l);
        func(func, nodes[node].r);
        answer[1].push_back(nodes[node].idx);
    };
    POST(POST, 0);
    
    return answer;
}