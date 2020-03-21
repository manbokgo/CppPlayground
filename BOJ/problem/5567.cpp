#include <bits/stdc++.h>

using namespace std;

vector<int> students[501];
int friends;
bool friends_chk[501];

void findFriends(int idx)
{
    for (int i = 0; i < students[idx].size(); i++)
    {
        if (idx == 1)
        {
            findFriends(students[idx][i]);
        }

        if (!friends_chk[students[idx][i]])
        {
            friends_chk[students[idx][i]] = true;
            ++friends;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        int first, second;
        cin >> first >> second;

        students[first].push_back(second);
        students[second].push_back(first);
    }

    friends_chk[1] = true;
    findFriends(1);
    cout << friends;
}