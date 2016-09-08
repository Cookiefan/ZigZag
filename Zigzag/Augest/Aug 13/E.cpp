#include <bits/stdc++.h>
#define maxn 52000
#define maxm 202000
#define bit 60
using namespace std;
typedef long long LL;

struct edge
{
	int s, t, next;
	LL val;
}e[maxm];

int n,m, num, tot;
int fir[maxn];
LL a[maxm], f[maxn];
int vis[maxn];

void dfs(int x, LL sum)
{
	vis[x]=1;
	f[x]=sum;
	for (int j=fir[x];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!vis[k])
			dfs(k, sum^e[j].val);
		else
			a[++num]=f[x]^f[k]^e[j].val;
	}
}

void add_edge(int x, int y, LL z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z;
	e[tot].next=fir[x]; fir[x]=tot;
}

int gauss(int n)
{
    int k=1;
    for (int i=bit;i;i--)
    {
        int p=0;
        for (int j=k;j<=n;j++) if ((a[j]>>(i-1))&1) {    p=j; break;    }
        if (p)
        {
            swap(a[k],a[p]);
            for (int j=1;j<=n;j++) if ((j!=k)&&((a[j]>>(i-1))&1)) a[j]^=a[k];
            k++;
        }
    }
    return k-1;
}


int main()
{
	int Case;
	scanf("%d",&Case);
	int x, y;
	LL z;
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		memset(vis,0,sizeof(vis));
		memset(fir,0,sizeof(fir));
		memset(f,0,sizeof(f));
		tot=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%I64d",&x,&y,&z);
			add_edge(x, y, z);
			add_edge(y, x, z);
		}
		num=0;
		dfs(1, 0);
		int cnt=gauss(num);
		LL ans=0;
		for (int i=1;i<=cnt;i++)
			ans^=a[i];
		printf("Case #%d: %I64d\n",o,ans);
	}
	return 0;	
}