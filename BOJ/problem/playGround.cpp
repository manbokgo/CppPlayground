#include <iostream>
#define M 1000000
using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    bool arr[M * 2 + 1] = {false};
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        arr[a + M] = true;
    }
    for (int i = 0; i <= M * 2; i++)
        if (arr[i])
            cout << i - M << '\n';
    return 0;
}
