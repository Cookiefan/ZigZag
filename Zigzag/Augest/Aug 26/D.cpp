#include <bits/stdc++.h>
#define maxn 52
#define maxm 2200
#define inf 99999999
using namespace std;
struct edge
{
	int s,t,val,next;
	double cost;
}e[maxm];

double p[maxn][maxm];
int v[maxn], fir[maxn], inque[maxn], pre[maxn];
double dis[maxn];
int n,m,st,ed,tot;
double ans;
double fare;

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

double fare_flow()
{
	double fare=0;
	int flow=0;
	while (find_path())
	{
		int tmp=inf;
		for (int j=pre[ed];j;j=pre[e[j].s]) tmp=min(tmp, e[j].val);
		for (int j=pre[ed];j;j=pre[e[j].s]) e[j].val-=tmp, e[j^1].val+=tmp;
		flow+=tmp;
		fare+=dis[ed]*tmp;
	}
	return fare;
}

void add_edge(int x, int y, int z, double w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

void init()
{
	st=0; ed=n+n+1; tot=1;
	memset(fir,0,sizeof(fir));
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				scanf("%lf",&p[i][j]);
		ans=0;
		for (int t=0;t<=m/n;t++)
		{
			int bg=t*n;
			init();
			for (int i=1;i<=n;i++)
				add_edge(st, i, 1, 0);
			for (int j=bg+1;j<=min(bg+n, m);j++)
				add_edge(n+j-bg, ed, 1, 0);
			for (int i=1;i<=n;i++)
				for (int j=bg+1;j<=min(bg+n, m);j++)
					add_edge(i, n+j-bg, 1, -p[i][j]);
			//for (int i=1;i<=tot;i++) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
			ans-=fare_flow();
		}
		printf("Case #%d: %.5f\n",o, ans);
	}

	return 0;
}