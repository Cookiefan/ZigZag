#include <bits/stdc++.h>
#define maxn 100200
#define maxm 500200
#define inf 1000000000
using namespace std;

int dis[maxn], vis[maxn];
double sum;
const double eps=1e-6;

int n,m,p;
//堆DJ
struct node
{
	int id,dis;
	node(){}
	node(int x,int y):id(x), dis(y){}
	friend bool operator <(node a,node b){ 
		return a.dis>b.dis;
	};
};

priority_queue<node> q;

struct edge
{
	int s, t, val, next;
}e[maxm];
int fir[maxn];
int tot;

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
}


int dij(int st, int ed)
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
			if (!vis[k]&&dis[i]+e[j].val<dis[k])
			{
				dis[k]=dis[i]+e[j].val;
				q.push(node(k,dis[k]));
			}
		}
	}
	return dis[ed];
}
int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&p);
		memset(fir,0,sizeof(fir));
		tot=0;
		int x, y, z;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		dij(n, 1);
		double l=0, r=(double)n*n*p, ans=0;
		while (r-l>=eps)
		{
			double mid=(l+r)*0.5, tmp=0;
			for (int i=1;i<=n;i++)
				tmp+=min((double)dis[i], (double)p+mid/n);
			if (mid-tmp>=eps)
			{
				r=mid;
				ans=mid;
			}
			else
				l=mid;
		}
		printf("%.5f\n",min((double)dis[1], ans/n+p));
	}
	return 0;
}