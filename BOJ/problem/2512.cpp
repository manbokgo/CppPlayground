#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int n, total;
	cin >> n;
	vector<int> budgets(n), sum(n);
	for (int i = 0; i < n; ++i) cin >> budgets[i];
	cin >> total;

	sortvec(budgets);
	
	for (int i = 1; i < n; ++i)
	{
		sum[i] = sum[i - 1] + budgets[i - 1]; // sum[i] = budget[0..i-1]
		if (sum[i] + budgets[i - 1] * (n - i) > total)
		{
			cout << (total - sum[i - 1]) / (n - i + 1);
			return 0;
		}
	}
	cout << budgets[n-1];
}