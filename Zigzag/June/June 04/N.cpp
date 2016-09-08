#include <bits/stdc++.h>
#define maxn 12000
#define maxm 42000
#define inf 99999999
using namespace std;
struct node1
{
	int id,dis,cost,num;
	node1(){}
	node1(int x, int z, int w, int n)
	{
		id=x; dis=z; cost=w; num=n;
	}
	friend bool operator <(node1 a,node1 b)
	{ 
		if (a.dis!=b.dis) return a.dis>b.dis;
		if (a.cost!=b.cost) return a.cost>b.cost;
		return a.num>b.num;
	};
};
struct node2
{
	int id,dis,cost,num;
	node2(){}
	node2(int x, int z, int w, int n)
	{
		id=x; dis=z; cost=w; num=n;
	}
	friend bool operator <(node2 a,node2 b)
	{ 
		if (a.cost!=b.cost) return a.cost>b.cost;
		if (a.dis!=b.dis) return a.dis>b.dis;
		return a.num>b.num;
	};
};

struct edge
{
	int s,t,val,cost,next;
}e[maxm];

int fir[maxn], dis[maxn], cost[maxn], vis[maxn], num[maxn];
int pre[maxn];
int n,m,tot,st,ed;

int dij1(int st, int ed)
{
	for (int i=0;i<=n;i++) dis[i]=inf;
	for (int i=0;i<=n;i++) cost[i]=inf;
	for (int i=0;i<=n;i++) num[i]=inf;
	memset(vis,0,sizeof(vis));
	priority_queue<node1> q;
	while (!q.empty()) q.pop();
	q.push(node1(st,0,0,1));
	dis[st]=0;
	cost[st]=0;
	num[st]=1;
	pre[st]=-1;
	while (!q.empty())
	{
		int i=q.top().id;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!vis[k] && node1(k,dis[i]+e[j].val,cost[i]+e[j].cost,num[i]+1)<node1(k,dis[k],dis[k],cost[k]))
			{
				dis[k]=dis[i]+e[j].val;
				cost[k]=cost[i]+e[j].cost;
				num[k]=num[i]+1;
				pre[k]=i;
				q.push(node1(k,dis[k],cost[k],num[k]));
			}
		}
	}
	printf("Distance = %d: ",dis[ed]);
	vector<int> l;
	l.clear();
	int tmp=ed;
	while (tmp!=-1)
	{
		l.push_back(tmp);
		tmp=pre[tmp];
	}
	int ss=l.size();
	for (int i=ss-1;i>=1;i--)
		cout<<l[i]<<" => ";
	cout<<l[0]<<endl;
}

int dij2(int st, int ed)
{
	for (int i=0;i<=n;i++) dis[i]=inf;
	for (int i=0;i<=n;i++) cost[i]=inf;
	for (int i=0;i<=n;i++) num[i]=inf;
	memset(vis,0,sizeof(vis));
	priority_queue<node2> q;
	while (!q.empty()) q.pop();
	q.push(node2(st,0,0,1));
	dis[st]=0;
	cost[st]=0;
	num[st]=1;
	pre[st]=-1;
	while (!q.empty())
	{
		int i=q.top().id;
		cout<<i<<endl;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!vis[k] && node2(k,dis[i]+e[j].val,cost[i]+e[j].cost,num[i]+1)<node2(k,dis[k],dis[k],cost[k]))
			{
				dis[k]=dis[i]+e[j].val;
				cost[k]=cost[i]+e[j].cost;
				num[k]=num[i]+1;
				pre[k]=i;
				q.push(node2(k,dis[k],cost[k],num[k]));
			}
		}
	}
	printf("Time = %d: ",cost[ed]);
	vector<int> l;
	l.clear();
	int tmp=ed;
	while (tmp!=-1)
	{
		l.push_back(tmp);
		tmp=pre[tmp];
	}
	int ss=l.size();
	for (int i=ss-1;i>=1;i--)
		cout<<l[i]<<" => ";
	cout<<l[0]<<endl;
}

void add_edge(int x, int y, int z, int w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w;
	e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
	scanf("%d%d",&n,&m);
	int x,y,z,w,d;
	tot=0;
	memset(fir,0,sizeof(fir));
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d%d",&x,&y,&d,&z,&w);
		add_edge(x,y,z,w);
		if (!d) add_edge(y,x,z,w);
	}
	scanf("%d%d",&st,&ed);
	dij2(st,ed);
	dij1(st,ed);
	return 0;
}