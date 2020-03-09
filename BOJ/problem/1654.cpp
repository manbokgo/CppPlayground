#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int k, n;
int lst[10000];

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);

	cin >> k >> n;
	int maxLength = 0;
	for (int i = 0; i < k; ++i)
	{
		cin >> lst[i];
		maxLength = max(maxLength, lst[i]);
	}

	// get upper_bound
	ll st = 0;
	ll en = (ll) maxLength + 1;
	while (st < en)
	{
		ll mid = (st + en) / 2;

		ll sum = 0;
		for (int i = 0; i < k; ++i)
			sum += lst[i] / mid;
		
		if (sum >= n) st = mid + 1;
		else en = mid;
	}
	cout << st - 1;
}