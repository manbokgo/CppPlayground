// URL: https://www.acmicpc.net/problem/14583
// Algo: 수학, 기하학

// Start:	241126 11 35
// Read:	0 2
// Think:	0 46
// Code:	0 2
// Total:	0 50

// https://mygumi.tistory.com/166

#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define all(x) x.begin(), x.end()
#define pb push_back

int main()
{
    fastio;

    double h, v;
    cin >> h >> v;

    const double d = sqrt(h * h + v * v);

    const double a = h / (h + d) * v;
    const double b = d / (h + d) * v;
    const double c = sqrt(h * h + a * a);

    const double width = c / 2;
    const double height = b * h / c;

    cout.precision(2);
    cout << fixed << width << ' ' << height;
}
