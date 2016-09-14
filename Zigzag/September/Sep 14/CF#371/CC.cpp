#include <bits/stdc++.h>
#define maxn 2200
#define sz 18
using namespace std;

typedef long long LL;
int n;
int a[maxn], b[maxn], c[maxn];
LL s[manx]
int f[maxn][maxn], g[maxn][maxn];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
		s[i]=s[i-1]+a[i];
	}
	sort(b+1, b+n+1);
	int m=unique(b+1, b+n+1)-b-1;

	for (int i=1;i<=m;i++) cout<<b[i]<<' '; cout<<endl;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			f[i][j]=s[i]-(2*b[j]-i+1)*i/2;
			for (int k=1;k<i;k++)
			{
				if ()
				f[i][j]=min(f[i][j], f[k][j-1]+s)
			}

		}
	
	printf("%d\n", f[n][m]);
	
	return 0;
}