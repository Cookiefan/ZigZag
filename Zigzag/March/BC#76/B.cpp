#pragma comment(linker, "/STACK:102400000,102400000") 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define maxn 220000
#define oo 1000000007
using namespace std;
typedef long long LL;
LL s[maxn],f[maxn];
int vis[maxn],fa[maxn],g[maxn];
vector<int> t[maxn];
int n,m;

LL rev(LL x)
{
	if (x==1) return 1;
	else return (oo-oo/x)*rev(oo%x)%oo;
}

void dfs(int x)
{
	f[x]=g[x]=1;
	s[x]=0;
	vis[x]=1;
	int num=t[x].size();
	for (int i=0;i<num;i++)
	{
		int y=t[x][i];
		if (!vis[y])
		{
			fa[y]=x;
			dfs(y);
			f[x]=f[x]*(f[y]+1)%oo;
			if ((f[y]+1)%oo!=0) g[x]=g[x]*(f[y]+1);
		}
	}
	for (int i=0;i<num;i++)
	{
		int y=t[x][i];
		if (y!=fa[x])
		{
			if ((f[y]+1)%oo!=0)
				s[x]=(s[x]+(s[y]*(f[x]*rev(f[y]+1)%oo)%oo))%oo;
			else
				s[x]=(s[x]+(s[y]*g[x]%oo))%oo;

		}
	}
	s[x]=(s[x]+f[x])%oo;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		int x;
		scanf("%d",&n);
		for (int i=1;i<=n;i++) t[i].clear();
		for (int i=2;i<=n;i++)
		{
			scanf("%d",&x);
			t[i].push_back(x);
			t[x].push_back(i);
		}
		memset(vis,0,sizeof(vis));
		memset(fa,0,sizeof(fa));
		dfs(1);
		LL ans=0;
		for (int i=1;i<=n;i++)
			ans=(ans+s[i])%oo;
		printf("%d\n",ans);
	}
	return 0;
}