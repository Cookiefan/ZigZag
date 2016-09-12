#include <bits/stdc++.h>
#define maxn 1020
#define maxm 500200
#define inf 999999999
using namespace std;

struct edge
{
	int s, t, val, cost, next;
}e[maxm];
int tot;
int fir[maxn], dis[maxn], pre[maxn], inque[maxn];
int n, m, st, ed, lim;

void add_edge(int x, int y, int z, int w)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x], fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

void init()
{
	st=0, ed=n+2; tot=1;
	memset(fir,0,sizeof(fir));
	memset(pre,0,sizeof(pre));
	memset(dis,0,sizeof(dis));
}

queue<int> q;
bool find_path()
{
	for (int i=st;i<=ed;i++) dis[i]=inf;
	while (!q.empty()) q.pop();
	q.push(st);
	dis[st]=0;
	inque[st]=1;
	while (!q.empty())
	{
		int x=q.front(); q.pop();
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
		inque[x]=0;
	}
	//cout<<dis[ed]<<' '<<endl;
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

string s;
string t[maxn];

int main()
{
	scanf("%d",&n);
	cin>>s;
	scanf("%d",&m);
	int x;
	init();
	for (int i=1;i<=m;i++)
	{
		cin>>t[i];
		int len=t[i].length();
		scanf("%d",&x);
		for (int j=0;j<=n-len;j++)
		{
			int flag=1;
			for (int k=0;k<len;k++)
				if (s[j+k]!=t[i][k])
				{
					flag=0;
					break;
				}
			if (flag) add_edge(j+1, j+len+1, 1, -x);
		}
	}
	scanf("%d",&lim);
	for (int i=1;i<=n;i++) add_edge(i, i+1, inf, 0);
	add_edge(st, 1, lim, 0);
	add_edge(n+1, ed, lim, 0);
	//for (int i=1;i<=tot;i+=2) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
	printf("%d\n", -fare_flow());
	return 0;
}