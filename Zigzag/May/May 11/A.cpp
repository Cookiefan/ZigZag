#include <bits/stdc++.h>
#define maxn 120
#define maxm 12000
using namespace std;

struct query
{
	int x, y, z, tp;
}q[maxm];

int a[maxn][maxn];
int n,m,p;

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	memset(a,0,sizeof(a));
	for (int i=1;i<=p;i++)
	{
		scanf("%d",&q[i].tp);
		if (q[i].tp==3)
			scanf("%d%d%d",&q[i].x, &q[i].y, &q[i].z);
		else if (q[i].tp==2)
			scanf("%d",&q[i].y);
		else 
			scanf("%d",&q[i].x);
	}
	for (int i=p;i>=1;i--)
	{
		if (q[i].tp==3)
			a[q[i].x][q[i].y]=q[i].z;
		else if (q[i].tp==2)
		{
			for (int k=n;k>=1;k--)
				a[k+1][q[i].y]=a[k][q[i].y];
			a[1][q[i].y]=a[n+1][q[i].y];
		}
		else
		{
			for (int k=m;k>=1;k--)
				a[q[i].x][k+1]=a[q[i].x][k];
			a[q[i].x][1]=a[q[i].x][m+1];
		}
	}
	// for (int i=1;i<=p;i++)
	// {
	// 	if (q[i].tp==1)
	// 	{
	// 		for (int k=1;k<=m;k++)
	// 			a[q[i].x][k-1]=a[q[i].x][k];
	// 		a[q[i].x][m]=a[q[i].x][0];
	// 	}
	// 	else if (q[i].tp==2)
	// 	{
	// 		for (int k=1;k<=n;k++)
	// 			a[k-1][q[i].y]=a[k][q[i].y];
	// 		a[n][q[i].y]=a[0][q[i].y];
	// 	}
	// 	else continue;
	// }
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			printf(j==m?"%d\n":"%d ",a[i][j]);
	return 0;
}