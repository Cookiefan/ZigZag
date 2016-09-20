#include <bits/stdc++.h>
#define maxn 2020
#define inf 999999999
#define oo 1000000007
using namespace std;

int f[maxn][maxn], g[maxn][maxn];
int a[maxn];
int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		m=inf;
		for (int i=0;i<n;i++) 
		{
			scanf("%d",&a[i]);
			m=min(m, a[i]);
		}
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for (int i=1;i<=n;i++)
		{
			f[i][0]=1;
			for (int j=1;j<=m;j++)
				f[i][j]=(f[i-1][j]+f[i][j-1])%oo;
		}
		printf("%d\n",f[n][m]);
	}
	return 0;
}