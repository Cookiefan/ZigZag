#include <bits/stdc++.h>
#define maxn 100200
using namespace std;

typedef long long LL;
int f[maxn], col[maxn], flag[maxn];
LL sum[maxn][2];
int n, m;

int find(int x, int y)
{
	if (f[x]==-1) return x;
	else
	{
		int fx=find(f[x], x);
		col[x]^=col[f[x]];
		return f[x]=fx;
	}
}

LL cnt(int x)
{
	if (flag[x])
	{
		LL tmp=sum[x][0]+sum[x][1];
		return tmp*(tmp-1)/2;
	}
	else
		return sum[x][0]*sum[x][1];
}

int main()
{
	scanf("%d%d",&n,&m);
	memset(f,-1,sizeof(f));
	memset(col, 0, sizeof(col));
	memset(sum, 0, sizeof(sum));
	memset(flag, 0, sizeof(flag));
	for (int i=1;i<=n;i++) sum[i][0]=1;
	int x, y;
	LL ans=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		int fx=find(x, 0), fy=find(y, 0);
		if (fx!=fy)
		{
			ans-=cnt(fx);
			ans-=cnt(fy);
			f[fx]=fy;
			flag[fy]|=flag[fx];
			col[fx]^=col[x]^col[y]^1;
			sum[fy][0]+=sum[fx][0^col[fx]];
			sum[fy][1]+=sum[fx][1^col[fx]];
			ans+=cnt(fy);
		}
		else
		{
			ans-=cnt(fx);
			if (col[x]==col[y]) flag[fx]=1;
			ans+=cnt(fx);
		}
		printf("%lld\n",ans);
	}
	return 0;
}