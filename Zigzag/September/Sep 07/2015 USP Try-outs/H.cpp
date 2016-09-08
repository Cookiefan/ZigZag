#include <bits/stdc++.h>
#define maxn 2200
using namespace std;

vector<int> t[maxn];
int col[maxn], vis[maxn], mch[maxn];
int n,m;

//匈牙利算法(二分图匹配)
bool match(int x)
{
	for (int y:t[x])
		if (!vis[y])
		{
			vis[y]=1;
			if ((!mch[y])||(match(mch[y])))
			{
				mch[y]=x;
				return 1;
			}
		}
	return 0;
}

int hungary()
{
	int tmp=0;
	memset(mch,0,sizeof(mch));
	for (int i=1;i<=n;i++)
		if (col[i]==0)
		{
			memset(vis,0,sizeof(vis));
			if (match(i)) tmp++;
		}
	return tmp;
}

void dfs(int x, int w)
{
	col[x]=w;
	vis[x]=1;
	for (int y:t[x])
		if (!vis[y])
			dfs(y, w^1);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			t[i].clear();
		int x, y;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			t[y].push_back(x);
		}
		memset(vis,0,sizeof(vis));
		dfs(1, 0);
		printf("%d\n",n-hungary());
	}
	return 0;
}