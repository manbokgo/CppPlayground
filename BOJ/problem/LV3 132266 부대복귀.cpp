// URL: https://school.programmers.co.kr/learn/courses/30/lessons/132266
// Algo: BFS

// Start:	240407 21 46
// Read:	0 1
// Think:	0 1
// Code:	0 10
// Total:	0 12 이게 왜 LV3?

#include <queue>
#include <vector>

using namespace std;

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination)
{
    vector<vector<int>> adj(n + 1);
    for (const auto& road : roads)
    {
        adj[road[0]].push_back(road[1]);
        adj[road[1]].push_back(road[0]);
    }

    vector<int> dist(n + 1, -1);
    queue<int> q, p;
    dist[destination] = 0;
    q.push(destination);

    int cDist = 0;
    while (!q.empty())
    {
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            for (int nxt : adj[cur])
            {
                if (dist[nxt] != -1) continue;
                dist[nxt] = cDist + 1;
                p.push(nxt);
            }
        }

        q.swap(p);
        ++cDist;
    }

    vector<int> answer;
    answer.reserve(sources.size());
    for (int src : sources)
    {
        answer.push_back(dist[src]);
    }

    return answer;
}
