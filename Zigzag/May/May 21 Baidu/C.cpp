#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#define inf 999999999
#define maxn 1200000
#define maxm 1200000
using namespace std;

struct edge
{
	int s,t,next;
}e[maxm];

int idg[maxn], fir[maxn], a[maxn];
int tot, n, m;

void add_edge(int x, int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		memset(fir,0,sizeof(fir));
		memset(idg,0,sizeof(idg));
		tot=0;
		scanf("%d%d",&n,&m);
		int x,y;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			add_edge(y,x);
			idg[x]++;
		}
		priority_queue<int, vector<int>, greater<int> >q;
		while (!q.empty()) q.pop();
		for (int i=1;i<=n;i++)
			if (idg[i]==0)
				q.push(i);
		int num=n;
		while (!q.empty())
		{
			int x=q.top();
			q.pop();
			a[num--]=x;
			for (int j=fir[x];j;j=e[j].next)
			{
				int y=e[j].t;
				if (!(--idg[y])) q.push(y);
			}
		}
		long long ans=0;
		int mi=inf;
		for (int i=1;i<=n;i++)
		{
			mi=min(mi, a[i]);
			ans+=mi;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}