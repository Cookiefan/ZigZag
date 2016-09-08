#include <bits/stdc++.h>
#define maxn 320
#define inf 99999999
using namespace std;

int f[50][maxn][maxn];
int n;
long long ans;

void floyd(int l, int r, int dep)
{
	memcpy(f[dep], f[dep-1], sizeof(f[dep]));
	for (int k=l;k<=r;k++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (f[dep][i][k]!=-1 && f[dep][k][j]!=-1)
				{
					if (f[dep][i][j]==-1)
						f[dep][i][j]=f[dep][i][k]+f[dep][k][j];
					else
						f[dep][i][j]=min(f[dep][i][j], f[dep][i][k]+f[dep][k][j]);
				}
}

void divide(int l, int r, int dep)
{
	if (l==r)
	{
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (i==l || j==l) continue;
				ans+=f[dep][i][j];
			}
		}
		return ;
	}
	int mid=(l+r)>>1;
	floyd(l, mid, dep+1);
	divide(mid+1, r, dep+1);
	floyd(mid+1, r, dep+1);
	divide(l, mid, dep+1);
}

int main()
{
	scanf("%d",&n);
	int x;
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&f[0][i][j]);
	ans=0;
	divide(1,n,0);
	printf("%I64d\n",ans);
	return 0;
}