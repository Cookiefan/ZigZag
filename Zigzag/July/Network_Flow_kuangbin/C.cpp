#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
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
	st=0; ed=500; num=0; tot=1;
	memset(fir,0,sizeof(fir));
	memset(last,0,sizeof(last));
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
}

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		init();
		map<string, int> rec;
		rec.clear();
		string x, y;
		for (int i=1;i<=n;i++)
		{
			cin>>x;
			rec[x]=i;
		}
		scanf("%d",&m);
		for (int i=1;i<=n;i++) add_edge(m+i, ed, 1);
		for (int i=1;i<=m;i++)
		{
			cin>>x>>y;
			if (rec.find(y)==rec.end()) rec[y]=++n;
			add_edge(st, i, 1);
			add_edge(i, m+rec[y], 1);
		}
		scanf("%d",&p);
		for (int i=1;i<=p;i++)
		{
			cin>>x>>y;
			if (rec.find(x)==rec.end()) rec[x]=++n;
			if (rec.find(y)==rec.end()) rec[y]=++n;
			add_edge(m+rec[x], m+rec[y], inf);
		}
		num=n+m+2;
		//for (int i=2;i<=tot;i++) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<endl;
		int ans=max_flow();
		printf("%d\n",m-ans);
	}
	return 0;
}