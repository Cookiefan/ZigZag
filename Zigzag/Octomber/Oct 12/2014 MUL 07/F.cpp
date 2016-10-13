#include <bits/stdc++.h>
#define maxn 220
using namespace std;

int d[maxn][maxn], b[maxn][maxn];
int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	int x, y, z, w;
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y, z, w;
		memset(d, 0, sizeof(d));
		memset(c, 0, sizeof(c));
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d%d",&x, &y, &z, &w);
			d[x][y]=z;
			c[x][y]=z+w;
		}
		for (int i=1;i<=n;i++)
		{
			LL insum=0, outsum=0
		}


	}
	return 0;
}