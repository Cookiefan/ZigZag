#include <bits/stdc++.h>
#define maxn 12
using namespace std;

int n,m;

int f[maxn][maxn];

int main()
{
	scanf("%d%d",&n,&m);
	f[0][1]=f[1][0]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			f[i][j]=f[i-1][j]*((1<<j)-1)
		}


	return 0;
}