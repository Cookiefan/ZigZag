#include <bits/stdc++.h>
#define maxn 12000
#define maxm 42000
#define inf 99999999
using namespace std;
struct node
{
	int id,dis;
	node(){}
	node(int x,int y)
	{
		id=x; dis=y;
	}
	friend bool operator <(node a,node b)
	{ 
		return a.dis>b.dis;
	};
};

struct edge
{
	int s,t,val,next;
}e[maxm];

priority_queue<node> q;
int fir[maxn], dis[maxn], vis[maxn];
int n,m,p,tot;

int dij(int st)
{
	for (int i=1;i<=n;i++) dis[i]=inf;
	memset(vis,0,sizeof(vis));
	while (!q.empty()) q.pop();
	q.push(node(st,0));
	dis[st]=0;
	while (!q.empty())
	{
		int i=q.top().id;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!vis[k] && dis[i]+e[j].val<dis[k])
			{
				dis[k]=dis[i]+e[j].val;
				q.push(node(k,dis[k]));
			}
		}
	}
	int mx=0, id=0;
	for (int i=1;i<=n;i++)
		if (dis[i]!=inf && dis[i]>mx)
		{
			mx=dis[i];
			id=i;
		}
	return id;
}

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	int x,y;
	memset(fir,0,sizeof(fir));
	tot=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y,1);
		add_edge(y,x,1);
	}
	for (int i=1;i<=p;i++)
	{
		scanf("%d",&x);
		printf("%d\n",dij(x));
	}
	return 0;
}
