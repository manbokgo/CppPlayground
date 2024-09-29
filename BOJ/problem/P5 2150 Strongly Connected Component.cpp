// URL: https://www.acmicpc.net/problem/2150
// Algo: SCC 타잔 기본

// Start:	240523 00 59
// Read:	0 2
// Think:	0 1
// Code:	0 5
// Total:	0 8

// 240522 G3 9466 텀 프로젝트 문제를 풀면서 떠오른 구상이 SCC 타잔 알고리즘이었다.
// 제대로 배운 후 그 문제에서 구현해봤던 걸, 거의 그대로 복붙해서 날먹했다

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

// SCC 타잔 알고리즘
vector<int> adj[10'001];
int label[10'001];
bool finish[10'001];
stack<int> S;

vector<vector<int>> answer;
int labelIdx = 1;

int Tarjan(int i)
{
    S.push(i);
    label[i] = labelIdx++;

    int parent = label[i];
    for (const auto j : adj[i])
    {
        if (!label[j]) parent = min(parent, Tarjan(j));
        else if (!finish[j]) parent = min(parent, label[j]);
    }

    if (parent == label[i]) // 내가 부모 노드다
    {
        vector<int> SCC;
        while (true)
        {
            int num = S.top();
            S.pop();

            SCC.pb(num);
            finish[num] = true;
            if (num == i) break;
        }

        sort(all(SCC));
        answer.pb(std::move(SCC));
    }

    return parent;
}

int main()
{
    fastio;

    int V, E;
    cin >> V >> E;

    for (int i = 1; i <= E; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
    }

    for (int i = 1; i <= V; ++i)
    {
        if (!label[i]) Tarjan(i);
    }

    sort(all(answer));
    cout << answer.size() << '\n';
    for (const auto& ans : answer)
    {
        for (const int num : ans) cout << num << ' ';
        cout << -1 << '\n';
    }
}
