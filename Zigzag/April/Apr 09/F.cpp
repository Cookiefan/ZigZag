#include <bits/stdc++.h>
#define maxn 420
#define maxm 1020
#define inf 999999999
using namespace std;
int f[maxn][maxn][maxm],px[maxn][maxn][maxm],py[maxn][maxn][maxm];
int cost[maxn][maxn],col[maxn][maxn];
int ansx[3*maxn],ansy[3*maxn];
int n,p,w;

int parity(int x)
{
	int tmp=0;
	while (x)
	{
		tmp+=(x&1);
		x=x>>1;
	}
	return tmp;
}

int main()
{
	scanf("%d%d%d",&n,&p,&w);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&cost[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&col[i][j]);
			col[i][j]--;
		}
	int lim=(1<<10)-1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=0;k<=lim;k++)
				f[i][j][k]=inf;
	f[1][1][1<<col[1][1]]=cost[1][1];
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (i==n && j==n) continue;
			for (int k=0;k<=lim;k++)
			{
				if (j==n || f[i][j][k]+cost[i][j]<f[i+1][j][k|(1<<col[i][j])])
				{
					f[i+1][j][k|(1<<col[i][j])]=f[i][j][k]+cost[i][j];
					px[i+1][j][k|(1<<col[i][j])]=-1;
					py[i+1][j][k|(1<<col[i][j])]=0;
				}
				if (i==n || f[i][j][k]+cost[i][j]<f[i][j+1][k|(1<<col[i][j])])
				{
					f[i][j+1][k|(1<<col[i][j])]=f[i][j][k]+cost[i][j];
					px[i][j+1][k|(1<<col[i][j])]=0;
					py[i][j+1][k|(1<<col[i][j])]=-1;
				}
			}
		}
	int min_col=inf, color;
	for (int k=0;k<=lim;k++)
		if (parity(k)<min_col && f[n][n][k]<=w)
		{
			min_col=parity(k);
			color=k;
		}
	int x=n,y=n, num=2*n-1;
	ansx[num]=x; ansy[num]=y;
	while (x!=1 || y!=1)
	{
		int nx=x+px[x][y][color];
		int ny=y+py[x][y][color];
		x=nx, y=ny;
		ansx[--num]=x; ansy[--num]=y;
	}
	printf("%d\n",min_col);
	for (int i=1;i<=2*n-1;i++)
		cout<<ansx<<' '<<ansy<<' ';	
	return 0;
}