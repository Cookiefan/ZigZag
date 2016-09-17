#include <bits/stdc++.h>
#define maxn 2200
#define maxm 82000
#define inf 999999999
using namespace std;
int dis[maxn], gap[maxn], vis[maxn], r[2][maxn];
int fir[maxn], last[maxn];
int cost[maxn][maxn];
int n,m,num,tot,st,ed;
vector<int> t[maxn];
struct edge
{
	int s,t,val,next;
}e[maxm];

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
}

void spfa(int st, int sign)
{
	queue<int> q;
	while (!q.empty()) q.pop();
	memset(vis,0,sizeof(vis));
	q.push(st);
	vis[st]=1;
	r[sign][st]=0;
	while (!q.empty())
	{
		int x=q.front(); q.pop();
		for (int y:t[x])
			if (!vis[y])
			{
				r[sign][y]=r[sign][x]+1;
				vis[y]=1;
				q.push(y);
			}
	}
}

int dfs(int x, int flow)
{
	if (x==ed) return flow;
	int sap=0;
	for (int j=last[x];j;j=e[j].next)
	{
		int y=e[j].t;
		if (e[j].val&&dis[x]==dis[y]+1)
		{
			last[x]=j;
			int tmp=dfs(y, min(e[j].val, flow-sap));
			e[j].val-=tmp;
			e[j^1].val+=tmp;
			sap+=tmp;
			if (sap==flow) return sap;
		}
	}
	if (dis[st]>=num) return sap;
	if (!(--gap[dis[x]])) dis[st]=num;
	++gap[++dis[x]];
	last[x]=fir[x];
	return sap;
}

int max_flow()
{
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
	gap[0]=num;
	memcpy(last,fir,sizeof(fir));
	int tmp=0;
	while (dis[st]<num) tmp+=dfs(st, inf);
	return tmp;
}

void init()
{
	st=1; ed=n; num=ed+1; tot=1;
	memset(fir,0,sizeof(fir));	
	memset(cost, 0, sizeof(cost));
	for (int i=1;i<=n;i++) t[i].clear();
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y, z;
		init();
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			t[x].push_back(y);
			t[y].push_back(x);
			cost[x][y]=cost[y][x]=z;
		}
		spfa(1, 0);
		spfa(n, 1);
		for (int i=1;i<=n;i++)
			for (int j:t[i])
				if (r[0][i]+1+r[1][j]==r[0][n])
				{
					add_edge(i, j, cost[i][j]);
					add_edge(j, i, 0);
				}
		printf("%d\n", max_flow());
	}
	return 0;
}