#include <bits/stdc++.h>
#define maxn 120000
#define maxm 220000
#define inf 99999999
#define ly 28
using namespace std;

struct edge
{
	int s,t,next;
}e[maxm];
int fir[maxn],dep[maxn],ans[maxn],idg[maxn];
int dfn[maxn],low[maxn],stack[maxn],col[maxn];
int fa[maxn][30];
int n,m,tot,tim,num,top;
vector<int> t[maxn];

void tarjan(int now)
{
    dfn[now]=low[now]=++tim;
	stack[++top]=now;
    v[now]=1;
	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k]) tarjan(k);
		if (v[k]<2) low[now]=min(low[now],low[k]);
	}
	if (dfn[now]==low[now])
	{
		num++;
		while (stack[top+1]!=now)
		{
			col[stack[top]]=num;
			v[stack[top--]]=2;
		}
    }
}

void set_father(int i)
{
	for (int k=1;k<=ly;k++)
		fa[i][k]=fa[fa[i][k-1]][k-1];
}

int get_father(int x,int y)
{
	if (dep[x]>dep[y]) swap(x,y);
	for (int i=ly;i>=0;i--)
		if (dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if (x==y) return x;
	for (int i=ly;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void add(int x, int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

void topo(int st)
{
	deque<int> que;
	que.clear();
	que.push_back(st);
	memset(dep,0,sizeof(dep));
	memset(fa,0,sizeof(fa));
	dep[st]=1;
	fa[st][0]=0;
	while (!que.empty())
	{
		int x=que.front();
		que.pop_front();
		for (int j=0,ss=d[x].size();j<ss;j++)
		{
			int y=e[j].t;
			if (!fa[[y][0]]) fa[y][0]=x;
			else fa[y][0]=get_father(fa[y][0], x);
			if (!(--idg[y]))
			{
				que.push_back(y);
				dep[y]=dep[fa[y][0]]+1;
				set_father(i);
			}
		}
	}
}

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		int x,y;
		for (int i=1;i<=n;i++) t[i].clear();
		memset(fir,0,sizeof(fir));
		memset(idg,0,sizeof(idg));
		tot=tim=num=top=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
			idg[y]++:
		}
		tarjan(n);
		for (int j=1;j<=m;j++)
			t[col[e[j].s]].push_back(col[e[j].t]);

		topo(col[n]);

		for (int i=1;i<=n;i++)
		{
			f[i]=i;
			for (int j=0,ss=p[i].size();j<ss;j++)
				f[i]=get_father(f[i], p[i][j]);
		}
		memset(ans,0,sizeof(ans));
		dfs(n);
		for (int i=1;i<=n;i++)
			printf(i==n?"%d\n":"%d ",ans[i]);
	}

	return 0;
}
