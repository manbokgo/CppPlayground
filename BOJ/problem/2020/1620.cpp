#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()

using namespace std;


bool cmp(const pair<int, string>& a, const pair<int, string>& b)
{
	return a.S < b.S;
}

bool pokeNameCompare(const pair<int, string>& value, const string& key)
{
	return value.S < key;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int n, m;
	vector<pair<int, string>> lst;

	cin >> n;
	cin >> m;
	
	lst.pb(mp(0, "dummy"));
	for (int i = 1; i <= n; ++i)
	{
		string tmp;
		cin >> tmp;
		lst.pb(mp(i, tmp));
	}

	vector<pair<int, string>> sortedLst = lst;
	sort(all(sortedLst), cmp);

	while (m--)
	{
		string findStr;
		cin >> findStr;
		if (findStr[0] >= '0' && findStr[0] <= '9')
			cout << lst[stoi(findStr)].S << '\n';
		else
			cout << (*lower_bound(all(sortedLst), findStr, pokeNameCompare)).F << '\n';
	}
}