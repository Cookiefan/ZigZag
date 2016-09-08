#include <bits/stdc++.h>
#define maxn 100020
#define maxm 200040
using namespace std;

struct edge
{
	int s,t,val,next;
}e[maxm];
int fir[maxn];
int a[maxn];
int n,m,k;
int ans, tot;

void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int x,y,z;
	tot=0;
	memset(fir,0,sizeof(fir));
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x, y, z);
		add_edge(y, x, z);
	}
	memset(a,0,sizeof(a));
	for (int i=1;i<=k;i++)
	{
		scanf("%d",&x);
		a[x]=1;
	}
	ans=-1;
	for (int i=1;i<=n;i++)
		if (a[i])
			for (int j=fir[i];j;j=e[j].next)
				if (!a[e[j].t])
				{
					if (ans==-1) ans=e[j].val;
					else ans=min(ans, e[j].val);
				}
	printf("%d\n",ans);

	return 0;
}