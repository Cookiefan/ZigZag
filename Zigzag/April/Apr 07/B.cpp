
#include <bits/stdc++.h>
using namespace std;

int n, p, q;
long long pos[2020];
int farest[2][2020];
int dp[2020][2020];

bool check(long long w)
{
	// printf("!!!%d:\n", w);
	if(p + q >= n) return true;

	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
		{
			if (pos[i]+w-1>=pos[j])
				farest[0][i]=j;
			if (pos[i]+2*w-1>=pos[j])
				farest[1][i]=j;
		}

	int tp, tq;
	tq = min(n, q);
	tp = min(n, p);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j <= n; j++) if(dp[i][j] != 0x3f3f3f3f)
		{
			int ed = farest[0][i+1];
			dp[ed][j+1] = min(dp[ed][j+1], dp[i][j]);
			ed = farest[1][i+1];
			dp[ed][j] = min(dp[ed][j], dp[i][j] + 1);
		}
	// for (int i = 0; i <= n; i++)
	// 	for (int j = 0; j <= n; j++)
	// 		printf("%d%c", dp[i][j], j == n ? '\n' : ' ');

	for (int i = 0; i <= tp; i++)
		if(dp[n][i] <= q) return true;
	// if(dp[n][p] <= q) return true;
	// else return false;
	// printf("false\n");
	return false;
	// printf("%s\n", now >= n? "yes" : "no");
	// return now >= n;
}


int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d", &n,&p,&q);
		for (int i = 1; i <= n; i++)
			scanf("%d", &pos[i]);
		sort(pos + 1, pos + n + 1);

		int low = 1, high = 1000000001, ans;
		int mid;
		while(low < high)
		{
			mid = (low + high) / 2;
			if(check(mid)) high = mid - 1;
			else low = mid + 1;
		}
		printf("%d\n", low);
	}
	return 0;
}
