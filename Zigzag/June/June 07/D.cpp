#include <bits/stdc++.h>
#define maxm 520000
#define maxn 220000
using namespace std;

struct edge
{
	int s, t, next, val, id;
}e[maxm];
int vis[maxm], mx[maxm], sum[maxm];
int fir[maxn], dg[maxn];
int tot, n;

void dfs(int x, int l, int fa)
{
	int one=0, two=0;
	for (int j=fir[x];j;j=e[j].next)
	{
		if (e[j].t==fa) continue; 
		if (!vis[j])
		{
			vis[j]=1;
			dfs(e[j].t, j, x);
		}
		if (mx[j]>one)
			two=one, one=mx[j];
		else
			two=max(two, mx[j]);
		sum[l]=max(sum[l], sum[j]);
	}
	//cout<<l<<' '<<one<<' '<<two<<endl;
	mx[l]=one+1;
	sum[l]=max(sum[l], one+two);
}

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
}
int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int x,y,z;
		tot=1;
		memset(fir,0,sizeof(fir));
		memset(dg,0,sizeof(dg));
		for (int i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			dg[x]++; dg[y]++;
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		vector <int> q; q.clear();
		for (int i=1;i<=n;i++)
			if (dg[i]==1)
				q.push_back(i);
		memset(mx,0,sizeof(mx));
		memset(vis,0,sizeof(vis));
		memset(sum,0,sizeof(sum));
		for (int ss=q.size(), i=0;i<ss;i++)
		{
			dfs(q[i], 0, 0);
		}
		int ans=99999999, edge_id;
		for (int j=2;j<=tot;j+=2)
		{
			//cout<<j/2<<' '<<sum[j]<<' '<<sum[j^1]<<endl;
			if (e[j].val*max(sum[j], sum[j^1])<ans)
			{
				ans=e[j].val*max(sum[j], sum[j^1]);
				edge_id=j/2;
			}
		}
		printf("Case #%d: %d\n",o,edge_id);
	}
	return 0;
}