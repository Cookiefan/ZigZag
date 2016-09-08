#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 520
#define maxm 22200
#define inf 999999999
using namespace std;
int n,k,m,st,ed,tot;
int p,q;
int a[maxn],s[maxn],t[maxn];
int dis[maxn],fir[maxn],v[maxn];
int ans;

struct edge
{
	int s,t,val,cost,next;
}e[maxm];

int dfs(int now,int flow)
{
    if (now==ed)
    {
        ans+=(int)dis[st]*flow;
        return flow;
    }
    int sap=0;    v[now]=1;
    for (int j=fir[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (!v[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
        {
            int tmp=dfs(k,min(e[j].val,flow-sap));
            e[j].val-=tmp;
            e[j^1].val+=tmp;
            sap+=tmp;
            if (sap==flow) return sap;
        }
    }
    return sap;
}

bool adjust()
{
    int tmp=inf;
    for (int i=st;i<=ed;i++) if (v[i])
        for (int j=fir[i];j;j=e[j].next)
        {
            int k=e[j].t;
            if (!v[k] && e[j].val) tmp=min(tmp,dis[k]+e[j].cost-dis[i]);
        }
    if (tmp==inf) return 0;
    for (int i=st;i<=ed;i++) if (v[i])
        dis[i]+=tmp;
    return 1;
}

bool judge()
{
	for (int i=2;i<=tot;i+=2)
		if (e[i].t==ed)
			if (e[i].val) return 0;
	return 1;
}

void add_edge(int x,int y,int z,int w)
{
    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
    e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&k);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		scanf("%d%d%d",&m,&p,&q);
		for (int i=1;i<=m;i++) scanf("%d%d",&s[i],&t[i]);
		st=0,ed=2*n+1,tot=1;
		memset(fir,0,sizeof(fir));
		memset(dis,0,sizeof(dis));
		add_edge(st,1,k,0);
		for (int i=1;i<n;i++)
			add_edge(i,i+1,inf,0);
		for (int i=p;i<=n;i++)
			add_edge(st,i,inf,q);
		for (int i=1;i<=n;i++)
			add_edge(i,ed,a[i],0);
		for (int i=1;i<=n;i++)
			add_edge(st,n+i,a[i],0);
		for (int i=1;i<n;i++)
			add_edge(n+i,n+i+1,inf,0);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				if (i+t[j]<=n)
					add_edge(n+i,i+t[j],inf,s[j]);
		// for (int i=2;i<=tot;i+=2) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
		ans=0;
		do 
        	do memset(v,0,sizeof(v));
        	while (dfs(st,inf));
    	while (adjust());
		if (judge())
    		printf("%d\n",ans);
    	else
    		printf("No solution\n");
		//for (int i=2;i<=tot;i+=2) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
	}	
	return 0;
}