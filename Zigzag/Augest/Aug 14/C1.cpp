#include <bits/stdc++.h>
#define maxn 100020
#define maxm 200020
using namespace std;

struct edge
{
	int s, t, next;
}e[maxm];
int tot;
int fir[maxn];
int vis[maxm], val[maxn], cost[maxm], dg[maxn];
int f[maxm], g[maxm], ans[maxn];
int n, o, step;

inline void dfs(int x, int p, int fa)
{
	f[p]=val[x]-2*cost[p];
	int m1=0;
	for (int j=fir[x];j;j=e[j].next)
		if (e[j].t!=fa)
		{
			if (vis[j]!=o)
			{
				vis[j]=o;
				dfs(e[j].t, j, x);	
			}
			if (f[j]>0) f[p]+=f[j], m1=max(m1, g[j]-f[j]);
			else m1=max(m1, g[j]);
		}
	g[p]=f[p]+m1+cost[p];
}

inline void down(int x, int p, int fa)
{
	int sum=0, tmp, cs, m1=0, m2=0;
	for (int j=fir[x];j;j=e[j].next)
	{
		if (f[j]>0)
		{
			sum+=f[j];
			tmp=g[j]-f[j];
		}
		else
			tmp=g[j];
		if (tmp>m1) m2=m1, m1=tmp, cs=j;
		else if (tmp>m2) m2=tmp;
	}
	ans[x]=val[x]+sum+m1;
	for (int j=fir[x];j;j=e[j].next)
		if (e[j].t!=fa)
		{
			f[j^1]=val[x]+sum-2*cost[j];
			if (f[j]>0) f[j^1]-=f[j];
			if (cs==j)
				g[j^1]=max(g[j^1], f[j^1]+m2+cost[j^1]);
			else
				g[j^1]=max(g[j^1], f[j^1]+m1+cost[j^1]);
			down(e[j].t, j, x);
		}
}

inline void add_edge(int x, int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

const int BufferSize=1<<16;
char buffer[BufferSize],*head,*tail;
inline char Getchar() {
    if(head==tail) {
        int l=fread(buffer,1,BufferSize,stdin);
        tail=(head=buffer)+l;
    }
    return *head++;
}
inline int read() {
    int x=0,f=1;char c=Getchar();
    for(;!isdigit(c);c=Getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=Getchar()) x=x*10+c-'0';
    return x*f;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (o=1;o<=Case;o++)
	{
		n=read();
		for (int i=1;i<=n;i++) val[i]=read();
		int x, y, z;
		tot=1;
		for (int i=0;i<=n;i++) fir[i]=0;
		for (int j=1;j<n;j++)
		{
			x=read(); y=read(); z=read();
			add_edge(x, y);
			cost[tot]=z;
			add_edge(y, x);
			cost[tot]=z;
		}
		for (int i=0;i<=tot;i++) f[i]=g[i]=0;
		dfs(1, 0, 0);
		down(1, 0, 0);
		printf("Case #%d:\n",o);
		for (int i=1;i<=n;i++) printf("%d\n",ans[i]);
	}
	return 0;
}