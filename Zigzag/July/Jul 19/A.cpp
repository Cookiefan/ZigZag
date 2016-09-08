#include <bits/stdc++.h>
#define maxn 340000
#define maxm 4200000
using namespace std;

struct edge
{
	int s,t,next;
	long long val;
}e[maxm];
struct dir
{
	int s, t, val;
	friend bool operator <(dir a, dir b)
	{
		return a.val<b.val;
	};
}d[maxm];
int n,m,tot;
int fir[maxn], f[maxn], fa[maxn];
long long sz[maxn], len;
double ans;

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
}

int find(int x)
{
	return f[x]==-1?x:f[x]=find(f[x]);
}

int merge(int x, int y)
{
	int fx=find(x), fy=find(y);
	if (fx!=fy)
	{
		f[fx]=fy;
		return 1;
	}
	else return 0;
}

void dfs(int x)
{
	sz[x]=1;
	for (int j=fir[x];j;j=e[j].next)
	{
		int y=e[j].t;
		if (!sz[y])
		{
			fa[y]=x;
			dfs(y);
			sz[x]+=sz[y];
		}
	}
}

void solve(int x)
{
	for (int j=fir[x];j;j=e[j].next)
	{
		int y=e[j].t;
		if (fa[x]!=y)
		{
			solve(y);
			ans+=(long long)sz[y]*(n-sz[y])*e[j].val;
		}
	}
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		tot=0;
		int x,y,z;
		memset(fir,0,sizeof(fir));
		memset(f,-1,sizeof(f));
		memset(fa,0,sizeof(fa));
		
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			d[i].s=x; d[i].t=y; d[i].val=z;	
		}
		len=0;
		sort(d+1, d+m+1);
		for (int i=1;i<=m;i++)
			if (merge(d[i].s, d[i].t))
			{
				add_edge(d[i].s, d[i].t, d[i].val);
				add_edge(d[i].t, d[i].s, d[i].val);
				len+=d[i].val;
			}
		memset(sz,0,sizeof(sz));
		//for (int i=1;i<=tot;i+=2) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<endl;
		dfs(1);
		ans=0;
		//for (int i=1;i<=n;i++) cout<<sz[i]<<endl;
		solve(1);
		ans=2.0*ans/((long long)n*(n-1));
		if (n==1) ans=0;
		printf("%I64d %.2f\n",len, ans);
	}
	return 0;
}