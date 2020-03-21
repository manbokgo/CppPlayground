#include <bits/stdc++.h>

using namespace std;

struct Node {
    int parent;
    vector<int> children;
};

Node nodes[50];
int n, root, delnum, ans;

void traverse(int idx)
{
    if (nodes[idx].children.empty())
    {
        ++ans;
        return;
    }

    for (int i = 0; i < nodes[idx].children.size(); i++)
    {
        traverse(nodes[idx].children[i]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int parent;
        cin >> parent;
        if (parent == -1)
        {
            root = i;
            continue;
        }
        nodes[i].parent = parent;
        nodes[parent].children.push_back(i);
    }

    cin >> delnum;
    if (delnum == root)
    {
        cout << 0;
        return 0;
    }

    vector<int>& vec = nodes[nodes[delnum].parent].children;
    vec.erase(std::remove(vec.begin(), vec.end(), delnum), vec.end());

    traverse(root);

    cout << ans;
}