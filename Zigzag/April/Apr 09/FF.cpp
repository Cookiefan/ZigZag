#include <bits/stdc++.h>
#define maxn 420
#define maxm 1050
#define inf 999999999
using namespace std;
int f[maxn][maxn][maxm];
int g[maxn][maxn],p[maxn][maxn];
int cost[maxn][maxn],col[maxn][maxn];
int v[20];
int ansx[3*maxn],ansy[3*maxn];
int n,m,w;

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
	cout<<sizeof(f)/1024/1024<<endl;
	scanf("%d%d%d",&n,&m,&w);
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
			{
				f[i][j][k]=inf;
				g[i][j]=inf;
			}

	f[1][1][1<<col[1][1]]=cost[1][1];
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (i==n && j==n) continue;
			for (int k=0;k<=lim;k++)
				if (f[i][j][k]<inf)
				{
					if (j==n || f[i][j][k]+cost[i+1][j]<f[i+1][j][k|(1<<col[i][j])])
						f[i+1][j][k|(1<<col[i][j])]=f[i][j][k]+cost[i+1][j];

					if (i==n || f[i][j][k]+cost[i][j+1]<f[i][j+1][k|(1<<col[i][j])])
						f[i][j+1][k|(1<<col[i][j])]=f[i][j][k]+cost[i][j+1];
				}
		}
	int min_col=inf, color;
	for (int k=0;k<=lim;k++)
		if (parity(k)<min_col && f[n][n][k]<=w)
		{
			min_col=parity(k);
			color=k;
		}
	if (min_col<inf)
		printf("%d\n",min_col);
	else
	{
		printf("-1\n");
		return 0;
	}

	for (int i=0;i<=9;i++)
	{
		v[i]=color&1;
		// cout<<v[i]<<' ';
		color=color>>1;
	}
	//cout<<endl;
	
	g[1][1]=cost[1][1];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (v[col[i][j]])
			{
				if (v[col[i+1][j]] && (j==n || g[i][j]+cost[i+1][j]<g[i+1][j]))
				{
					g[i+1][j]=g[i][j]+cost[i+1][j];
					p[i+1][j]=1;
				}
				if (v[col[i][j+1]] && (i==n || g[i][j]+cost[i][j+1]<g[i][j+1]))
				{
					g[i][j+1]=g[i][j]+cost[i][j+1];
					p[i][j+1]=-1;
				}
			}
	int x=n, y=n, num=2*n-1;
	ansx[num]=x, ansy[num]=y;
	while (x>1 || y>1)
	{
		//cout<<x<<' '<<y<<endl;
		if (p[x][y]==1)
			x--;
		else
			y--;
		num--;
		ansx[num]=x, ansy[num]=y;
	}
	for (int i=1;i<=2*n-1;i++)
		cout<<ansx[i]<<' '<<ansy[i]<<' ';	
	return 0;
}