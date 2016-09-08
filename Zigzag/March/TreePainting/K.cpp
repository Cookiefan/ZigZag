#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define maxn 120
using namespace std;
vector<int> t[maxn];
int vis[maxn];
int n,m;
bool found;

bool dfs(int x)
{
	if (x==n) found=1;
	vis[x]=1;
	int num=t[x].size();
	for (int i=0;i<num;i++)
	{
		int k=t[x][i];
		if (!vis[k]) dfs(k);
	}
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x,y;
		for (int i=1;i<=n;i++) t[i].clear();
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
		}
		found=0;
		memset(vis,0,sizeof(vis));
		dfs(1);
		if (found) printf("^_^\n");
		else printf("T_T\n");
	}
	return 0;
}