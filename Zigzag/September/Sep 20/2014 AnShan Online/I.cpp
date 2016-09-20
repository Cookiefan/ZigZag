#include <bits/stdc++.h>
#define maxn 220
using namespace std;

vector<int> t[maxn];
int vis[maxn];
int bel[maxn], idg[maxn];
typedef pair<int,int> pii;
pii f[maxn],a[maxn], b[maxn];
int n, st;

void dfs(int x, int cnt)
{
	vis[x]=1;
	f[x]=a[x];
	for (int y: t[x])
	{
		if (!vis[y]) dfs(y, cnt);
		if (bel[x]==0)
		{
			if (f[y].first>f[x].first)
				f[x]=f[y];
		}
		else
		{
			if (f[y].second==cnt)
				f[x]=f[y];
			else if (f[y].first<f[x].first)
				f[x]=f[y];
		}
	}
}

void solve(int x)
{
	vis[x]=1;
	f[x]=a[x];
	for (int y: t[x])
	{
		if (!vis[y]) solve(y);
		if (bel[x]==0)
		{
			if (f[y].first>f[x].first)
				f[x]=f[y];
		}
		else
		{
			if (f[y].second>f[x].second)
				f[x]=f[y];
		}
	}
}

bool cmp(pii a, pii b)
{
	return a.second>b.second;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int num;
		char c;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(idg,0,sizeof(idg));
		for (int i=1;i<=n;i++)
		{ 
			t[i].clear();
			scanf("%d",&num);
			if (num!=0)
			{
				int k;
				for (int j=0;j<num;j++)
				{
					scanf("%d",&k);
					idg[k]++;
					t[i].push_back(k);
				}
				scanf(" %c",&c);
				bel[i]=(c=='X');
			}
			else
				scanf("%d%d",&a[i].first,&a[i].second);
		}
		for (int i=1;i<=n;i++)
			if (!idg[i])
				st=i;

		memset(vis,0,sizeof(vis));
		solve(st);

		int ans1=f[st].second, ans2=0;

		memcpy(b, a, sizeof(a));
		sort(b+1, b+n+1, cmp);
		for (int i=n;i>=1;i--)
		{
			memset(vis,0,sizeof(vis));
			dfs(st, i);
			if (f[st].first==b[i].first)
			{
				ans2=b[i].second;
				break;
			}
		}
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}