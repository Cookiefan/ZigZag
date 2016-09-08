#include <bits/stdc++.h>
#define maxn 220000
#define maxm 520000
#define inf 999999999999999LL
using namespace std;
typedef long long llg;

struct node
{
	int id; llg dis;
	node(){}
	node(int x,llg y): id(x),dis(y){}
	friend bool operator <(node a,node b){ return a.dis>b.dis;}
};
struct edge
{
	int s, t, wisdom, next;
	llg val;
}e[maxm];
int fir[maxn], vis[maxn];
llg dis[maxn];
int n,m,p,tot;

llg dij(int wis)
{
	for (int i=1;i<=n;i++) dis[i]=inf;
	memset(vis,0,sizeof(vis));
	priority_queue<node> q;
	while (!q.empty()) q.pop();
	q.push(node(1,0));
	dis[1]=0;
	while (!q.empty())
	{
		int i=q.top().id;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			if (e[j].wisdom>wis) continue;
			int k=e[j].t;
			if (!vis[k]&&dis[i]+e[j].val<dis[k])
			{
				dis[k]=dis[i]+e[j].val;
				q.push(node(k,dis[k]));
			}
		}
	}
	return dis[n];
}

void add_edge(int x, int y, int z, int w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].wisdom=w;
	e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&p);
		tot=0;
		memset(fir,0,sizeof(fir));
		int x, y, z, w;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d%d",&x,&y,&z,&w);
			add_edge(x,y,z,w);
			add_edge(y,x,z,w);
		}
		int l=1, r=1000000000, ans=-1;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (dij(mid)<p)
			{
				r=mid-1;
				ans=mid;
			}
			else
				l=mid+1;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}