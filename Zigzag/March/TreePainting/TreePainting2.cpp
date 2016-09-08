#include <bits/stdc++.h>
using namespace std;
#define maxn 120000
int n;
struct edge
{
	int s,t,next;
}e[maxn*2];
int fir[maxn],vis[maxn];
int tot,ans;

void add(int x,int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

void dfs(int x)
{
	vis[x]=1;
	int sum=0;
	for (int j=fir[x];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!vis[k])
		{
			sum++;
			dfs(k);
		}
	}
	if (x==1) ans+=(sum+1)/2;
	else ans+=sum/2;
}

int main()
{
	freopen("data.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int x,y;
		tot=0;
		memset(fir,0,sizeof(fir));
		for (int i=2;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
		}
		memset(vis,0,sizeof(vis));
		ans=0;
		dfs(1);
		cout<<ans<<endl;
	}
	return 0;
}