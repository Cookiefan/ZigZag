#include <bits/stdc++.h>
#define maxn 120
#define inf 999999999999999999ll
using namespace std;
typedef long long LL;
typedef pair<LL, int> pli;
priority_queue<pli, vector<pli>, greater<pli> > q[maxn];
LL f[maxn][maxn][maxn];
int cost[maxn][maxn];
int col[maxn];
int n, m, p;

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	for (int i=1;i<=n;i++) scanf("%d",&col[i]);
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&cost[i][j]);
	if (m==1)
	{
		if (p!=1) printf("-1\n");
		else
		{
			LL tmp=0;
			for (int i=1;i<=n;i++)
				tmp+=(col[i]!=1)*cost[i][1];
			printf("%I64d\n",tmp);
		}
		return 0;
	}
	for (int i=0;i<=n;i++)
		for (int j=0;j<=p;j++)
			for (int k=0;k<=m;k++)
			{
				f[i][j][k]=inf;
				//f[0][1][i]=0;
			}
	q[0].push(pli(0,0));
	q[0].push(pli(0,0));
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=min(i, p);j++)
		{
			pli now, tmp;
			if (q[j-1].size()>=2)
			{
				now=q[j-1].top(); q[j-1].pop();
				tmp=q[j-1].top(); q[j-1].push(now);
			}
			if (col[i])
			{	
				int k=col[i];
				f[i][j][k]=f[i-1][j][k];
				if (q[j-1].size()>=2)
				{
					if (now.second==k)
						f[i][j][k]=min(f[i][j][k], tmp.first);
					else
						f[i][j][k]=min(f[i][j][k], now.first);
				}
			}
			else
			{
				for (int k=1;k<=m;k++)
				{
					f[i][j][k]=min(f[i][j][k], f[i-1][j][k]+cost[i][k]);
					if (q[j-1].size()>=2)
					{
						if (now.second==k)
							f[i][j][k]=min(f[i][j][k], tmp.first+cost[i][k]);
						else
							f[i][j][k]=min(f[i][j][k], now.first+cost[i][k]);
					}
				}
			}
		}
		for (int j=0;j<=p;j++)
		{
			while (!q[j].empty()) q[j].pop();
			for (int k=1;k<=m;k++)
				q[j].push(pli(f[i][j][k], k));
		}
	}
	LL tmp=inf;
	for (int i=1;i<=m;i++)
		tmp=min(tmp, f[n][p][i]);
	if (tmp==inf)
		printf("-1\n");
	else
		printf("%I64d\n",tmp);

	return 0;
}