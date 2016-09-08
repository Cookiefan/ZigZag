#include <bits/stdc++.h>
#define maxn 1200
#define maxm 1200000
using namespace std;
int n,m,num,tot,ans;
int h[maxn][maxn],w[maxn][maxn];
int f[maxm];

struct edge
{
	int s,t,v;
	edge(){}
	edge(int s, int t, int v):s(s),t(t),v(v){}
	friend bool operator <(edge a, edge b)
	{
		return a.v<b.v;
	}
}e[maxm];

int find(int x)
{
	return f[x]==-1?x:f[x]=find(f[x]);
}

bool merge(int x, int y)
{
	int fx=find(x), fy=find(y);
	if (fx!=fy)
	{
		f[fx]=fy;
		return 1;
	}
	return 0;
}

int main()
{
	freopen("Escape.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=0;i<=n;i++)
			for (int j=0;j<m;j++)
				scanf("%d",&w[i][j]);
		for (int i=0;i<n;i++)
			for (int j=0;j<=m;j++)
				scanf("%d",&h[i][j]);
		tot=0;
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				if (i==0) e[tot++]=edge(i*m+j, n*m, w[i][j]);
				if (i==n-1) e[tot++]=edge(i*m+j, n*m, w[i+1][j]);
				else e[tot++]=edge(i*m+j, (i+1)*m+j, w[i+1][j]);

				if (j==0) e[tot++]=edge(i*m+j, n*m, h[i][j]);
				if (j==m-1) e[tot++]=edge(i*m+j, n*m, h[i][j+1]);
				else e[tot++]=edge(i*m+j, i*m+j+1, h[i][j+1]);
			}
		memset(f,-1,sizeof(f));
		sort(e, e+tot);
		ans=0;
		for (int i=0;i<n*m;i++)
			//if (merge(e[i].s, e[i].t))
			{
				//cout<<e[i].s/m+1<<','<<e[i].s%m+1<<' '<<e[i].t/m+1<<','<<e[i].t%m+1<<endl;
				ans+=e[i].v;
			}
		printf("%d\n",ans);
	}
	
	return 0;
}