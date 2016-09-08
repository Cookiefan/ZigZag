// #pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#define maxn 200020
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
	g[p]=val[x]-cost[p];
	for (int j=fir[x];j;j=e[j].next)
		if (e[j].t!=fa)
		{
			if (vis[j]!=o)
			{
				vis[j]=o;
				dfs(e[j].t, j, x);	
			}
			if (f[j]>0) f[p]+=f[j];
		}
	for (int j=fir[x];j;j=e[j].next)
		if (e[j].t!=fa)
		{
			if (f[j]>0) 
				g[p]=max(g[p], f[p]-f[j]+g[j]+cost[p]);
			else
				g[p]=max(g[p], f[p]+g[j]+cost[p]);
		}
}

inline void add_edge(int x, int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}

int main()
{
	// int size = 256 << 20; // 256MB
	// char *p = (char*)malloc(size) + size;
	// __asm__("movl %0, %%esp\n" :: "r"(p));
	 freopen("C.in","r",stdin);
	 freopen("C.out","w",stdout);
	int Case;
	scanf("%d",&Case);
	for (o=1;o<=Case;o++)
	{
		n=read();
		for (int i=1;i<=n;i++) val[i]=read();
		int x, y, z;
		tot=1;
		for (int i=0;i<=n;i++) fir[i]=0, dg[i]=0;;
		for (int j=1;j<n;j++)
		{
			x=read(); y=read(); z=read();
			add_edge(x, y);
			cost[tot]=z;
			add_edge(y, x);
			cost[tot]=z;
			dg[x]++; dg[y]++;
		}
		f[0]=g[0]=0;
		
		for (int i=1;i<=1;i++)
			{
				ans[i]=0;
				dfs(i, 0, 0);
				ans[i]=max(ans[i], f[0]);
				ans[i]=max(ans[i], g[0]);
			}

		// for (int i=1;i<=n;i++)
		// 	if (dg[i]>1)
		// 	{
		// 		ans[i]=0;
		// 		dfs(i, 0, 0);
		// 		ans[i]=max(ans[i], f[0]);
		// 		ans[i]=max(ans[i], g[0]);
		// 	}
		cout<<step<<endl;
		printf("Case #%d:\n",o);
		for (int i=1;i<=n;i++) printf("%d\n",ans[i]);
	}
	return 0;
}