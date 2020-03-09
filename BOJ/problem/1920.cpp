#include <bits/stdc++.h>

#define pb push_back
#define all(x) x.begin(), x.end()
#define sortvec(x) sort(all(x))

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int n, m;
	vector<int> lst;

	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		lst.pb(tmp);
	}
	sortvec(lst);
	
	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		int find;
		cin >> find;
		cout << binary_search(all(lst), find) << '\n';
	}
}