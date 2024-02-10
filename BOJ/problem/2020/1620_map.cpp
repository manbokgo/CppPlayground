#include <bits/stdc++.h>

#define pb push_back

using namespace std;

int n, m;
string intToString[100001];
// vector<string> intToString;
map<string, int> stringToInt;

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);

	cin >> n;
	cin >> m;

	// intToString.pb("dummy");
	for (int i = 1; i <= n; ++i)
	{
		string tmp;
		cin >> tmp;
		stringToInt[tmp] = i;
		intToString[i] = tmp;
		// intToString.pb(tmp);
	}

	while (m--)
	{
		string findStr;
		cin >> findStr;
		if (findStr[0] >= '0' && findStr[0] <= '9')
			cout << intToString[stoi(findStr)] << '\n';
		else
			cout << stringToInt[findStr] << '\n';
	}
}