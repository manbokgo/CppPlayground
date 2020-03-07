#include <bits/stdc++.h>
using namespace std;

bool compare(const string a, const string b)
{
	if (a.length() == b.length()) return a < b;
	return a.length() < b.length();
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	vector<string> lst(n);
	for (int i = 0; i < n; ++i) cin >> lst[i];
	
	sort(lst.begin(), lst.end(), compare);
	lst.erase(unique(lst.begin(), lst.end()), lst.end());

	for (const auto& val : lst)
		cout << val << '\n';
}