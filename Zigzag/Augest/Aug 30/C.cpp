#include <bits/stdc++.h>
#define maxn 120
#define inf 999999999999999999ll
using namespace std;
typedef long long LL;
LL f[maxn][maxn];
int cost[maxn][maxn];
LL sc[maxn][maxn];
int col[maxn];
LL pure[maxn][maxn];
int n, m, p;


int samecolor(int x, int y)
{
	int tmp=0;
	for (int i=x;i<=y;i++)
		if (tmp && col[i]!=tmp) return -1;
		else tmp=col[i];
	return tmp;
}


int main()
{
	scanf("%d%d%d",&n,&m,&p);
	for (int i=1;i<=n;i++) scanf("%d",&col[i]);
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&cost[i][j]);
			sc[i][j]=sc[i-1][j]+cost[i][j];
		}
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
		{
			int color=samecolor(i,j);
			if (color==-1) pure[i][j]=-1;
			else if (color==0)
			{
				LL tmp=inf;
				for (int k=1;k<=m;k++)
					if (sc[j][k]-sc[i-1][k]<tmp)
						tmp=sc[j][k]-sc[i-1][k];
				pure[i][j]=tmp;
			}
			else
				pure[i][j]=sc[j][color]-sc[i-1][color];
			cout<<i<<' '<<j<<' '<<' '<<color<<' '<<pure[i][j]<<endl;
		}
	for (int k=0;k<=p;k++)
		for (int i=0;i<=n;i++)
			f[k][i]=inf;
	f[0][0]=0;
	for (int k=1;k<=p;k++)
		for (int i=1;i<=n;i++)
		{
			f[k][i]=inf;
			for (int j=0;j<=i-1;j++)
				if (pure[j+1][i]!=-1 && f[k-1][j]!=inf)
				{
					f[k][i]=min(f[k][i], f[k-1][j]+pure[j+1][i]);
					if (k==2 && i==2) cout<<pure[j+1][i]<<endl;
				}
			cout<<k<<' '<<i<<' '<<f[k][i]<<endl;
		}
	if (f[p][n]==inf)
		printf("-1\n");
	else
		printf("%d\n",f[p][n]);

	return 0;
}