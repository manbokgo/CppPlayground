#include <bits/stdc++.h>
using namespace std;
#define mp make_pair

int adj[1000000];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int, int>> dimension;
    int cell = 1;

    string s;
    getline(cin, s);
    
    istringstream iss(s);
    int size;
    while (iss >> size)
    {
        dimension.push_back(mp(size, cell));
        cell *= size;
    }

    queue<int> Q;
    int visit_num = 0;
    int total_num = 0;
    for (int i = 0; i < cell; i++)
    {
        cin >> adj[i];
        if (adj[i] == 1)
        {
            ++visit_num;
            Q.push(i);
        }
        total_num += (adj[i] != -1);
    }

    int day = 0;
    while (!Q.empty())
    {
        auto cur = Q.front();
        Q.pop();
        day = max(day, adj[cur]);

        for (auto &&dim : dimension)
        {
            int size = dim.first;
            int cell = dim.second;
            int pos = cur / cell % size;
            for (int i = -1; i < 2; i += 2)
            {
                int offset = cur + i * cell;
                if (pos + i >= 0 && pos + i < size && adj[offset] == 0)
                {
                    adj[offset] = adj[cur] + 1;
                    ++visit_num;
                    Q.push(offset);
                }
            }
        }
    }

    cout << (total_num == visit_num ? day - 1 : -1);
}