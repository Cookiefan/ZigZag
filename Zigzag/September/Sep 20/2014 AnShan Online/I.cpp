#include <bits/stdc++.h>
#define maxn 220
#define inf 99999999
using namespace std;

vector<int> t[maxn];
int vis[maxn];
int bel[maxn], idg[maxn];
typedef pair<int,int> pii;
pii f[maxn],a[maxn];
vector<pii>b;
int n, st;

void dfs(int x, int cnt)
{
	vis[x]=1;
	if (bel[x]==0) f[x]=a[x];
	else f[x]=pii(inf, inf);
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
			//cout<<y<<": "<<f[y].first<<' '<<f[y].second<<endl;
			//cout<<x<<' '<<y<<' ';
			if (f[y].second==cnt)
			{
				f[x]=f[y];
				//cout<<1<<endl;
			}
			if (f[x].second!=cnt && f[y].first<f[x].first)
			{
				f[x]=f[y];
				//cout<<2<<endl;
			}
		}
	}
	//cout<<x<<' '<<f[x].first<<' '<<f[x].second<<endl;
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
	return a.second<b.second;
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
		memset(bel,0,sizeof(bel));
		memset(idg,0,sizeof(idg));
		b.clear();
		for (int i=1;i<=n;i++)
		{ 
			a[i]=pii(0,0);
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
			{
				scanf("%d%d",&a[i].first,&a[i].second);
				b.push_back(a[i]);
			}
		}
		for (int i=1;i<=n;i++)
			if (!idg[i])
				st=i;

		memset(vis,0,sizeof(vis));
		solve(st);

		int ans1=f[st].second, ans2=0;

		sort(b.begin(), b.end(), cmp);
		for (int i=b.size()-1;i>=0;i--)
		{
			memset(vis,0,sizeof(vis));
			dfs(st, b[i].second);
			// cout<<f[st].first<<endl;
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