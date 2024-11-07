// URL: https://www.acmicpc.net/problem/5430
// Algo: 파싱, 덱

// Start:	241107 20 19
// Read:	0 2
// Think:	0 4
// Code:	0 20
// Total:	0 26

// 귀찮은 구현만 하면 되는 굉장히 재미없는 문제

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

deque<int> Split(const string& str, const string& delim)
{
    size_t st = 0, en;
    const size_t delimLen = delim.length();

    deque<int> result;
    while ((en = str.find(delim, st)) != string::npos)
    {
        string token = str.substr(st, en - st);
        st = en + delimLen;
        result.push_back(stoi(token));
    }

    if (st != str.size())
        result.push_back(stoi(str.substr(st)));

    return result;
}

int main()
{
    fastio;

    int T;
    cin >> T;

    while (T--)
    {
        string cmd;
        cin >> cmd;

        int n;
        cin >> n;

        string arrInput;
        cin >> arrInput;

        deque<int> arr = Split(arrInput.substr(1, arrInput.size() - 2), ",");

        bool isReverse = false;
        bool isError = false;
        for (const char c : cmd)
        {
            if (c == 'R')
            {
                isReverse = !isReverse;
                continue;
            }

            if (arr.empty())
            {
                isError = true;
                break;
            }

            if (!isReverse) arr.pop_front();
            else arr.pop_back();
        }

        if (isError)
        {
            cout << "error\n";
            continue;
        }

        cout << "[";

        if (isReverse) reverse(all(arr));
        for (int i = 0; i < arr.size(); ++i)
        {
            cout << arr[i];
            if (i != arr.size() - 1) cout << ',';
        }

        cout << "]\n";
    }
}
