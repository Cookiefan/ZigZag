#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int a[maxn][maxn];
int n,m;
const int low=12;

bool judge()
{
	int mid=n/2, s=0,t=0;
	for (int i=1;i<=m;i++)
	{
		if (abs(a[mid-1][i]-a[mid][i])<=low) s++;
		if (abs(a[1][i]-a[n][i])<=low) t++;
	}
	return (double)s*1.0/m<=(double)t*1.0/m;
}

int main()
{
	//freopen("all.in","r",stdin);
	//freopen("all.out","w",stdout);
	int Case=0;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				scanf("%d",&a[i][j]);
		if (judge()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}