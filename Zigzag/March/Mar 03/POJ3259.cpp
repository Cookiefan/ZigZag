#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define maxn 1200
#define maxm 22000
#define inf 2000000000
using namespace std;

deque<int>que;
int dis[maxn];
int fir[maxn],inque[maxn],freq[maxn],vis[maxn];
int n,m,w,tot;

struct edge
{
	int s,t,val,next;
}e[maxm];

void add_edge(int x,int y,int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
}

bool spfa(int st)
{
	for (int i=1;i<=n;i++) dis[i]=inf;
	memset(inque,0,sizeof(inque));
	memset(freq,0,sizeof(freq));
	dis[st]=0;
	que.push_back(st);
	inque[st]=1;
	freq[st]=1;
	while (!que.empty())
	{
		int now=que.front();
		que.pop_front();
		inque[now]=0;
		vis[now]=1;
		for (int j=fir[now];j;j=e[j].next)
		{
			int k=e[j].t;
			if (dis[k]>dis[now]+e[j].val)
			{
				dis[k]=dis[now]+e[j].val;
				if (!inque[k])
				{
					que.push_back(k);
					inque[k]=1;
					if (++freq[k]>n) return 1;
				}
			}
		}
	}
	return 0;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&w);
		int x,y,z;
		tot=0;
		memset(fir,0,sizeof(fir));
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		for (int i=1;i<=w;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x,y,-z);
		}
		memset(vis,0,sizeof(vis));
		bool neg=0;
		for (int i=1;i<=n;i++)
			if (!vis[i])
				if (spfa(i)) neg=1;
		printf(neg?"YES\n":"NO\n");
	}
	return 0;
}