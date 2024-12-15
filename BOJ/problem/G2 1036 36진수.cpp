// URL: https://www.acmicpc.net/problem/1036
// Algo: 그리디, 큰 수, 구현

// Start:	241214 23 39
// Read:	0 2
// Think:	0 15
// Code:	1 14
// Total:	1 31

// G4 1339 단어 수학과 비슷하게, 자릿수까지 고려하여 등장하는 문자의 개수를 모두 센다.
// 그 문자를 Z(35)로 바꾼다면 개수*(35-i) 만큼의 변화가 발생하고, 이 변화가 제일 큰 순으로 k를 골라
// 기존 합에 더하면 정답이 된다.

// 로직 자체는 어렵지 않은데 BigInteger가 없는 C++에서는 36^50의 개수를 감당할 수 없다....
// vector<int> digit을 담은 구조체 등으로 32진법 BigInteger를 구현해 덧셈, 비교 등을 만들어 줘야 하는데
// 그냥 무지성 10진법 BigInteger가 기본 내장된 파이썬하면 안 될 까...?

// 꾸역꾸역 구현했다. 만들고 놓고 보니 간단한 거 같긴 함.

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

struct decimal36
{
    vector<int> dig = vector<int>(60);
    int sz = 0;

    void Carry()
    {
        for (int i = 0; i < 59; ++i)
        {
            if (dig[i]) sz = i + 1;
            if (dig[i] >= 36)
            {
                dig[i + 1] += dig[i] / 36;
                dig[i] %= 36;
            }
        }
    }

    friend bool operator<(const decimal36& lhs, const decimal36& rhs)
    {
        if (lhs.sz != rhs.sz)
            return lhs.sz < rhs.sz;

        for (int i = lhs.sz - 1; i >= 0; --i)
        {
            if (lhs.dig[i] != rhs.dig[i])
                return lhs.dig[i] < rhs.dig[i];
        }

        return false;
    }

    friend bool operator<=(const decimal36& lhs, const decimal36& rhs) { return !(rhs < lhs); }
    friend bool operator>(const decimal36& lhs, const decimal36& rhs) { return rhs < lhs; }
    friend bool operator>=(const decimal36& lhs, const decimal36& rhs) { return !(lhs < rhs); }
};

int CharToDigit36(char c)
{
    if (c - '0' <= 9) c -= '0';
    else c -= 'A' - 10;
    return (int)c;
}

char Digit36ToChar(int i)
{
    if (i <= 9) i += '0';
    else i += 'A' - 10;
    return (char)i;
}

decimal36 expected[36];
decimal36 sum;

int main()
{
    fastio;

    int n;
    cin >> n;

    string str;
    while (n--)
    {
        cin >> str;
        for (int i = str.size() - 1; i >= 0; --i)
        {
            int num = CharToDigit36(str[i]);
            expected[num].dig[str.size() - i - 1] += 35 - num;
            sum.dig[str.size() - i - 1] += num;
        }
    }

    for (decimal36& exp : expected)
        exp.Carry();

    int k;
    cin >> k;

    sort(expected, expected + 36, greater<>());
    for (int i = 0; i < k; ++i)
    {
        const auto& [dig, sz] = expected[i];
        for (int j = 0; j < sz; ++j)
            sum.dig[j] += dig[j];
    }

    sum.Carry();
    if (sum.sz == 0) 
    {
        cout << '0';
        return 0;
    }

    for (int i = sum.sz - 1; i >= 0; --i)
    {
        cout << Digit36ToChar(sum.dig[i]);
    }
}
