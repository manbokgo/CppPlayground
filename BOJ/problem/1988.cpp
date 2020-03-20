#include <bits/stdc++.h>

using namespace std;

int dp[3000][2]{}, n, b, x;
int main()
{
	scanf("%d%d", &n, &b);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		for (int j = b - 1; j > 0; --j) // WA!! 슬라이드 윈도우!
		{
			dp[j][0] = max(dp[j][0], dp[j][1]);
			dp[j][1] = max(dp[j - 1][0], dp[j - 1][1] + x);
		}
	}
	printf("%d", max(dp[b - 1][0], dp[b - 1][1]));
}
