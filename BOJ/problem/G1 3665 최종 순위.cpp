// URL: https://www.acmicpc.net/problem/3665
// Algo: 위상 정렬

// Start:	240723 18 48
// Read:	0 2
// Think:	0 11
// Code:	0 11
// Total:	0 24

// 다 풀고 나서 찾아보니 확실한 순위를 찾을 수 없는 ?의 경우는 아예 존재하지 않는다.

// 예제1을 예시로 들면, [2, 4] 쌍만 나왔을 때  2와 3이 indegree가 2로 동일한 것 같지만
// 데이터가 정합하다면 [3, 4]도 반드시 나와야하므로 indegree가 최종적으로 같은 경우는 존재하지 않고,
// 만약 정합하지 않다면 그냥 IMPOSSIBLE임

// 따라서 데이터가 정합하다면 indegree가 중복인 경우가 없는만큼 adj 간선 배열 필요없이
// 각 숫자의 순위와 indegree만 알면, indegree 순으로 쭉 출력하는 것으로 빠르게 정답을 구할 수 있음

// https://www.acmicpc.net/source/80675872

// + indegree 배열 없이 간선 배열의 정보를 통해 정렬을 하여 답을 구하는 방식
// https://justicehui.github.io/icpc/2019/08/31/BOJ3665/

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int arr[501];
bool adj[501][501];
int indegree[501];

int main()
{
    fastio;
    int T;
    cin >> T;

    while (T--)
    {
        memset(arr, -1, sizeof(arr));
        memset(adj, false, sizeof(adj));
        memset(indegree, 0, sizeof(indegree));

        int n;
        cin >> n;

        for (int i = 0; i < n; ++i)
            cin >> arr[i];

        for (int i = 0; i < n; ++i)
        {
            const int st = arr[i];
            for (int j = i + 1; j < n; ++j)
            {
                const int en = arr[j];
                adj[st][en] = true;
                ++indegree[en];
            }
        }

        int m;
        cin >> m;

        while (m--)
        {
            int a, b;
            cin >> a >> b;
            if (adj[b][a]) swap(a, b);

            adj[a][b] = false;
            ++indegree[a];

            adj[b][a] = true;
            --indegree[b];
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i)
        {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> answer;
        answer.reserve(n);

        bool notSure = false;
        while (!q.empty())
        {
            if (q.size() > 1)
            {
                notSure = true;
                break;
            }

            const int num = q.front();
            q.pop();
            answer.pb(num);

            for (int i = 1; i <= n; ++i)
            {
                if (!adj[num][i]) continue;
                --indegree[i];
                if (indegree[i] == 0) q.push(i);
            }
        }

        if (notSure) cout << '?';
        else if (answer.size() != n) cout << "IMPOSSIBLE";
        else for (const int num : answer) cout << num << ' ';
        cout << '\n';
    }
}
