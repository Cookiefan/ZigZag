#include <bits/stdc++.h>
#define maxn 1020
#define maxm 20200
#define inf 999999999999999999LL
using namespace std;//负环spfa
typedef long long LL;
struct edge
{
	int s,t,next,flag;
	LL val;
}e[maxm];
struct tii
{
	int x, y;
	LL z;
	tii(){}
	tii(int x, int y, LL z):
	x(x), y(y), z(z){}
};
tii p[maxm];
LL dis[2][maxn];
int vis[maxn], fir[maxn];
int n,m,tot,st,ed;
LL len;

struct node
{
	int id;
	LL dis;
	node(){}
	node(int x,LL y)
	{
		id=x; dis=y;
	}
	friend bool operator <(node a,node b)
	{ 
		return a.dis>b.dis;
	};
};

priority_queue<node> q;

void dij(int st, int id)
{
	for (int i=0;i<=n;i++) dis[id][i]=inf;
	memset(vis,0,sizeof(vis));
	while (!q.empty()) q.pop();
	q.push(node(st,0));
	dis[id][st]=0;
	while (!q.empty())
	{
		int i=q.top().id;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!vis[k]&&dis[id][i]+e[j].val<dis[id][k])
			{
				dis[id][k]=dis[id][i]+e[j].val;
				q.push(node(k,dis[id][k]));
			}
		}
	}
}

void add_edge(int x, int y, LL z, int w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].flag=w;
	e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
	scanf("%d%d%d%d%d",&n,&m,&len,&st,&ed);
	int x, y, z;
	memset(fir,0,sizeof(fir));
	tot=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		p[i]=tii(x, y, z);
		if (z==0)
		{
			add_edge(x, y, inf, i);
			add_edge(y, x, inf, i);
		}
		else
		{
			add_edge(x, y, z, 0);
			add_edge(y, x, z, 0);
		}
	}
	dij(st, 0);
	LL ans1=dis[0][ed];

	for (int i=1;i<=tot;i++)
		if (e[i].flag!=0)
			e[i].val=1;
	dij(st, 0);
	LL ans2=dis[0][ed];

	dij(ed, 1);
	vector<int> tmp;
	tmp.clear();
	if (ans1>=len && ans2<=len)
	{
		x=st;
		while (x!=ed)
		{
			for (int j=fir[x];j;j=e[j].next)
			{
				y=e[j].t;
				if (dis[0][x]+e[j].val+dis[1][y]==dis[0][ed])
				{
					x=y;
					if (e[j].flag!=0)
						tmp.push_back(e[j].flag);
					break;
				}
			}
		}

		for (int j:tmp) p[j].z=1;
		if (tmp.size()>0) p[tmp[0]].z+=(len-ans2);

		for (int i=1;i<=m;i++)
			if (p[i].z==0)
				p[i].z=inf;

		printf("YES\n");
		for (int i=1;i<=m;i++)
			printf("%d %d %I64d\n",p[i].x, p[i].y, p[i].z);
	}
	else
		printf("NO\n");
	return 0;

}