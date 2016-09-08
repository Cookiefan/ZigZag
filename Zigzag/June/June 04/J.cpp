#include <bits/stdc++.h>
#define maxn 120
using namespace std;

int a[maxn][maxn],b[maxn][maxn];
int n,m,p;

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	int x,y,z;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if (z==1) a[x][y]=a[y][x]=1;
		else b[x][y]=b[y][x]=1;
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (i!=k && j!=k)
					a[i][j]=max(a[i][j],a[i][k]&a[k][j]);
	for (int i=1;i<=p;i++)
	{
		scanf("%d%d",&x,&y);
		if (a[x][y] && !b[x][y]) printf("No problem\n");
		else if (!a[x][y] && !b[x][y]) printf("OK\n");
		else if (a[x][y] && b[x][y]) printf("OK but...\n");
		else printf("No way\n");
	}

	return 0;
}