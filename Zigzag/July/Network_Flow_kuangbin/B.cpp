#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 1020
#define maxm 1220000
#define inf 999999999
using namespace std;

int fir[maxn], last[maxn], dis[maxn], gap[maxn];
int st, ed, n, m, p, num, tot;

struct edge
{
	int s,t,val,next;
}e[maxm];

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].next=fir[y]; fir[y]=tot;
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
	gap[0]=num;
	memcpy(last,fir,sizeof(fir));
	int tmp=0;
	while (dis[st]<num) tmp+=dfs(st, inf);
	return tmp;
}

void init()
{
	st=0; ed=2*n+m+p+1; num=ed+1; tot=1;
	memset(fir,0,sizeof(fir));
	memset(last,0,sizeof(last));
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
}

int main()
{
	while (scanf("%d%d%d",&n,&m,&p)!=EOF)
	{
		init();
		int x,y,z;
		for (int i=1;i<=m;i++) add_edge(st, i, 1);
		for (int i=1;i<=n;i++) add_edge(m+i,n+m+i,1);
		for (int i=1;i<=p;i++) add_edge(2*n+m+i, ed, 1);		
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			for (int j=1;j<=x;j++)
			{
				scanf("%d",&z);
				add_edge(z,m+i,1);
			}
			for (int j=1;j<=y;j++)
			{
				scanf("%d",&z);
				add_edge(n+m+i,2*n+m+z,1);
			}
		}
		int ans=max_flow();
		printf("%d\n",ans);
	}
	return 0;
}
/*
30 40 60
6 6 7 23 24 29 33 40 7 8 20 25 41 48
3 1 19 25 28 58
5 5 11 12 19 24 36 7 10 14 17 24
4 6 9 13 32 40 3 5 29 32 41 45
3 2 18 20 31 28 52
3 5 10 17 35 12 19 40 53 55
3 8 2 8 31 3 8 9 18 21 42 47 55
5 7 8 11 14 29 40 4 7 13 17 28 45 49
5 2 11 18 28 32 35 27 29
3 8 7 38 40 4 11 17 26 28 30 38 55
3 2 5 9 25 12 33
4 5 2 13 23 24 3 12 34 52 59
4 3 1 21 30 35 6 23 40
2 9 30 31 18 23 27 31 34 38 51 57 58
6 6 8 13 18 28 30 32 1 30 41 50 57 59
4 5 5 19 28 32 38 42 43 44 59
3 3 4 21 32 13 16 33
4 6 12 15 20 28 5 6 21 38 43 57
2 2 6 17 36 48
3 3 29 32 35 2 6 54
1 4 18 11 19 48 55
2 3 2 35 8 10 57
2 10 4 29 3 4 5 13 17 20 31 40 41 59
3 3 7 12 17 35 45 57
3 2 20 21 24 2 6
5 5 5 16 18 29 35 25 30 36 39 41
4 5 5 27 33 35 33 35 45 49 55
0 6 7 18 29 34 46 60
3 11 27 31 39 11 14 23 25 29 32 36 40 44 48 56
1 5 21 5 17 25 47 49
*/