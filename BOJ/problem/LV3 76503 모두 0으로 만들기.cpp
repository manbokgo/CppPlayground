// URL: https://school.programmers.co.kr/learn/courses/30/lessons/76503
// Algo: DFS, 그리디

// Start:	240328 19 52
// Read:	0 1
// Think:	0 1
// Code:	0 20
// Total:   0 22

// 리프 노드들은 무조건 가중치만큼 연산이 필요하다. 리프 노드의 가중치를 부모에게 몰빵하고
// 리프 노드들을 지운다면 그 부모가 이제 새 리프 노드가 되었으므로... 반복

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> nodes;
vector<int> adj[300'000];
ll ans = 0;


void DFS(int node, int parent)
{
    for (auto nNode : adj[node])
    {
        if (nNode == parent) continue;
        DFS(nNode, node);
    }
    
    ans += abs(nodes[node]);
    nodes[parent] += nodes[node]; // 루트노드에서는 0 += 0이면 상관없으므로 예외 안 해도 됨
}


long long solution(vector<int> a, vector<vector<int>> edges) {
    nodes.resize(a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        nodes[i] = a[i];
    }
    
    for (auto& edge : edges)
    {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }
    
    DFS(0, 0);
    return nodes[0] ? -1 : ans;
}