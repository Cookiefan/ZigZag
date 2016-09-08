#include <bits/stdc++.h>
#define maxn 120000
#define maxm 220000
using namespace std;

typedef pair<int,int> pii;

struct edge
{
	int s, t, val, next;
}e[maxm];
int fir[maxn];
int dep[maxn], dis[maxn], dfn[maxn];
int id[maxm];
pii st[maxm][30];
int n,m,tot,sec;

inline int read()
{
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}

inline void dfs(int x)
{
	id[++sec]=x;
	dfn[x]=sec;
	for (int j=fir[x];j;j=e[j].next)
	{
		int y=e[j].t;
		if (!dfn[y])
		{
			dep[y]=dep[x]+1;
			dis[y]=dis[x]+e[j].val;
			dfs(y);
			id[++sec]=x;
		}
	}
}

inline int get_father(int x, int y)
{
	x=dfn[x], y=dfn[y];
	if (x>y) swap(x,y);
	int k=log2(y-x+1);
	if (st[x][k].first<st[y-(1<<k)+1][k].first)
		return st[x][k].second;
	else
		return st[y-(1<<k)+1][k].second;
}
inline void set_father(int n)
{
	for (int i=1;i<=n;i++)
		st[i][0]=pii(dep[id[i]],id[i]);
	int low=log2(n);
	for (int k=1;k<=low;k++)
		for (int i=1;i<=n;i++)
			if (st[i][k-1].first<st[i+(1<<(k-1))][k-1].first)
				st[i][k]=st[i][k-1];
			else
				st[i][k]=st[i+(1<<(k-1))][k-1];
}

inline int get_dis(int x, int y)
{
	int lca=get_father(x,y);
	return dis[x]-dis[lca]+dis[y]-dis[lca];
}

inline void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
}

pii mx[maxn*8];

void update(int x)
{
	int lc=x<<1, rc=x<<1|1;
	
}

void build(int x, int l, int r)
{
	if (l==r)
	{
		mx[x]=pii(l, r);
		return ;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	update(x);
}


int main()
{
	scanf("%d",&n);
	int x,y,z;
	tot=0;
	memset(fir,0,sizeof(fir));
	for (int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	sec=0;
	memset(dfn,0,sizeof(dfn));
	dep[1]=dis[1]=0;
	dfs(1);
	set_father(sec);
	build(1,1,n);
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
	}
	return 0;
}