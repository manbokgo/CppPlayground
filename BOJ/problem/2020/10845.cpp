#include <bits/stdc++.h>

using namespace std;

int myqueue[10001];
int m_head = 0;
int m_tail = 0;

void push(int input)
{
    myqueue[++m_tail] = input;
}

int pop()
{
    if (m_head == m_tail)
        return -1;
    return myqueue[++m_head];
}

int size()
{
    return m_tail - m_head;
}

int empty()
{
    return m_head == m_tail ? 1 : 0;
}

int front()
{
    if (m_head == m_tail)
        return -1;
    return myqueue[m_head + 1];
}

int back()
{
    if (m_head == m_tail)
        return -1;
    return myqueue[m_tail];
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
        else if (cmd == "front")
        {
            cout << front() << '\n';
        }
        else if (cmd == "back")
        {
            cout << back() << '\n';
        }
    }
}