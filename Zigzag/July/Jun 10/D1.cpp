#include <bits/stdc++.h>
#define maxn 120
using namespace std;
int a[maxn][maxn];
int v[maxn][maxn];
int n,m;
char c;

void dfs(int x, int y)
{
	v[x][y]=1;
	if (a[x+1][y]==1 && !v[x+1][y]) dfs(x+1,y);
	if (a[x][y+1]==1 && !v[x][y+1]) dfs(x,y+1);
	if (a[x-1][y]==1 && !v[x-1][y]) dfs(x-1,y);
	if (a[x][y-1]==1 && !v[x][y-1]) dfs(x, y-1);
}
int main()
{
	scanf("%d%d",&n,&m);
	memset(a,0,sizeof(a));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&c);
			if (c=='B') a[i][j]=1;
			else a[i][j]=0;
		}
	int ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]==1 && !v[i][j])
			{
				dfs(i,j);
				ans++;
			}
	printf("%d\n",ans);
	return 0;
}