#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 220
#define maxm 220000
#define inf 999999999
using namespace std;

int fir[maxn], last[maxn], dis[maxn], gap[maxn];
int st, ed, n, m, num, tot;

struct edge
{
	int s,t,val,next;
}e[maxm];
struct sign
{
	int p[20];
	sign(){}
	sign(int x)
	{
		for (int i=0;i<m;i++) p[i]=x;
	}
	friend bool operator ==(sign a, sign b)
	{
		for (int i=0;i<m;i++)
			if (a.p[i]+b.p[i]==1) return 0;
		return 1;
	};
}insg[maxn], outsg[maxn];

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=y; e[tot].val=0; e[tot].next=fir[y]; fir[y]=tot;
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
	memcpy(last,fir,sizeof(last));
	int tmp=0;
	while (dis[st]<num) tmp+=dfs(st, inf);
	return tmp;
}

void init()
{
	st=0; ed=2*n+1; num=2*n+2; tot=1;
	memset(fir,0,sizeof(fir));
	memset(last,0,sizeof(last));
	memset(dis,0,sizeof(dis));
	memset(last,0,sizeof(last));
}

int main()
{
	while (scanf("%d%d",&m,&n)!=EOF)
	{
		int x,y,z;
		init();
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			add_edge(2*i-1, 2*i, x);
			for (int k=0;k<m;k++)
				scanf("%d",&insg[i].p[k]);
			if (insg[i]==sign(0)) add_edge(st, i*2-1, inf);
			for (int k=0;k<m;k++)
				scanf("%d",&outsg[i].p[k]);
			if (outsg[i]==sign(1)) add_edge(i*2, ed, inf);
		}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
			{
				if (i==j) continue;
				if (outsg[i]==insg[j])
					add_edge(2*i, 2*j-1, inf);
			}
		int ans=max_flow();
		printf("%d ", ans);
		int sum=0;
		for (int j=2;j<=tot;j+=2)
		{
			int s=e[j].s, t=e[j].t;
			if (s!=st && t!=ed && (s+1)/2!=(t+1)/2 && e[j^1].val)
				sum++;
		}
		printf("%d\n",sum);
		for (int j=2;j<=tot;j+=2)
		{
			int s=e[j].s, t=e[j].t;
			if (s!=st && t!=ed && (s+1)/2!=(t+1)/2 && e[j^1].val)
				printf("%d %d %d\n",(s+1)/2, (t+1)/2, e[j^1].val);
		}
	}
	return 0;
}
/*
3 4
15  0 0 0  0 1 0
10  0 0 0  0 1 1
30  0 1 2  1 1 1
3   0 2 1  1 1 1
*/