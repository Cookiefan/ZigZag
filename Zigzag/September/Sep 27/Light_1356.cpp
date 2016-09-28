#include <bits/stdc++.h>
#define maxn 40020
#define inf 99999999
using namespace std;

struct edge
{
	int s, t, val, next;
	edge(){}
	edge(int s, int t, int val, int next):
	s(s), t(t), val(val), next(next){}
};
vector<edge> e;
int fir[maxn], last[maxn];
int dis[maxn], gap[maxn];
int a[maxn], col[maxn];
int v[500022];
int num, st, ed, n;
void add_edge(int x, int y, int z)
{
	e.push_back(edge(x, y, z, fir[x]));
	fir[x]=e.size()-1;
	e.push_back(edge(y, x, 0, fir[y]));
	fir[y]=e.size()-1;
}
int dfs(int x, int flow)
{
	if (x==ed) return flow;
	int sap=0;
	for (int j=last[x];j!=-1;j=e[j].next)
	{
		int y=e[j].t;
		if (e[j].val && dis[x]==dis[y]+1)
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
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
	memcpy(last, fir, sizeof(fir));
	gap[0]=num;
	int tmp=0;
	while (dis[st]<num) tmp+=dfs(st, inf);
	return tmp;
}

void init()
{
	st=0; ed=n+1; num=ed+1;
	e.clear();
	memset(fir,-1,sizeof(fir));
	
}

int np[500022];
vector<int> prime;

void get_prime(int m)
{
	prime.clear();
	memset(np,0,sizeof(np));
	for (int i=2;i<=m;i++)
	{
		if (!np[i]) prime.push_back(i);
		for (int j=0;j<prime.size() && i*prime[j]<=m;j++)
		{
			np[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}

int main()
{
	int Case;
	scanf("%d",&Case);
	get_prime(500000);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		init();

		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		memset(v,0,sizeof(v));
		for (int i=1;i<=n;i++)
			v[a[i]]=i;
		
		memset(col,0,sizeof(col));
		for (int i=1;i<=n;i++)
			for (int j=0;j<prime.size();j++)
			{
				int x=a[i];
				while (x%prime[j]==0)
				{
					x/=prime[j];
					col[i]^=1;
				}
			}
		for (int i=1;i<=n;i++)
			if (col[i]==0)
				add_edge(st, i, 1);
			else
				add_edge(i, ed, 1);

		for (int i=1;i<=n;i++)
			for (int j=0;j<prime.size();j++)
			{
				if (prime[j]>a[i]) break;
				if (a[i]%prime[j]==0 && v[a[i]/prime[j]])
				{
					if (col[i]==0)
						add_edge(i, v[a[i]/prime[j]], inf);
					else
						add_edge(v[a[i]/prime[j]], i, inf);
				}
			}

		// for (int j=2;j<=tot;j+=2)
		// 	cout<<e[j].s<<' '<<e[j].t<<' '<<e[j].val<<endl;

		int ans=n-max_flow();
		printf("Case %d: %d\n",o, ans);
	}
	return 0;
}