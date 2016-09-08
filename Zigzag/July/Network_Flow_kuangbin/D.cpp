#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#define maxn 12000
#define maxm 2200000
#define inf 999999999
using namespace std;

int n,m,tot,st,ed;
int fir[maxn], dis[maxn], pre[maxn], inque[maxn];
char c;
vector<int> h, p;

struct edge
{
	int s, t, val, cost, next;
}e[maxm];

void add_edge(int x, int y, int z, int w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x], fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

void init()
{
	st=0, ed=n*m+1; tot=1;
	memset(fir,0,sizeof(fir));
	memset(dis,0,sizeof(dis));
}

bool find_path()
{
	for (int i=st;i<=ed;i++) dis[i]=inf;
	queue<int> q;
	q.push(st);
	dis[st]=0;
	inque[st]=1;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		inque[x]=0;
		for (int j=fir[x];j;j=e[j].next)
		{
			int y=e[j].t;
			if (e[j].val && dis[y]>dis[x]+e[j].cost)
			{
				dis[y]=dis[x]+e[j].cost;
				pre[y]=j;
				if (!inque[y]) q.push(y), inque[y]=1;
			}
		}
	}
	return dis[ed]<inf;
}

int fare_flow()
{
	int fare=0, flow=0;
	while (find_path())
	{
		int tmp=inf;
		for (int j=pre[ed];j;j=pre[e[j].s]) tmp=min(tmp, e[j].val);
		for (int j=pre[ed];j;j=pre[e[j].s]) e[j].val-=tmp, e[j^1].val+=tmp;
		flow+=tmp;
		fare+=tmp*dis[ed];
	}
	return fare;
}


int main()
{
	while (scanf("%d%d",&n,&m) && (n+m))
	{
		h.clear();
		p.clear();
		init();
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				scanf(" %c",&c);
				if (c=='H') h.push_back(i*m+j);
				if (c=='m') p.push_back(i*m+j);
			}
		int s=h.size(), t=p.size();
		for (int i=0;i<s;i++) add_edge(st, i+1, 1, 0);
		for (int i=0;i<t;i++) add_edge(s+i+1, ed, 1, 0);
		for (int i=0;i<s;i++)
			for (int j=0;j<t;j++)
			{
				int d=abs(h[i]/m-p[j]/m)+abs(h[i]%m-p[j]%m);
				add_edge(i+1, s+j+1, 1, d);
			}
		//for (int i=2;i<=tot;i+=2) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
		printf("%d\n",fare_flow());
	}

	return 0;
}

