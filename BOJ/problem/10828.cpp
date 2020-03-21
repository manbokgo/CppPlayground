#include <bits/stdc++.h>

using namespace std;

int myqueue[10000];
int myqueue_idx = 0;

void push(int input)
{
    myqueue[myqueue_idx++] = input;
}

int pop()
{
    if (myqueue_idx == 0)
        return -1;
    return myqueue[--myqueue_idx];
}

int size()
{
    return myqueue_idx;
}

int empty()
{
    return myqueue_idx == 0 ? 1 : 0;
}

int top()
{
    if (myqueue_idx == 0)
        return -1;
    return myqueue[myqueue_idx - 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--)
    {
        string cmd;
        cin >> cmd;

        if (cmd == "push")
        {
            int data;
            cin >> data;
            push(data);
        }
        else if (cmd == "pop")
        {
            cout << pop() << '\n';
        }
        else if (cmd == "size")
        {
            cout << size() << '\n';
        }
        else if (cmd == "empty")
        {
            cout << empty() << '\n';
        }
        else if (cmd == "top")
        {
            cout << top() << '\n';
        }
    }
}