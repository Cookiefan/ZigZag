#include <bits/stdc++.h>
#define maxn 3200
#define sz 18
using namespace std;

typedef long long LL;
int n;
int a[maxn], b[maxn], c[maxn];
LL f[maxn][maxn];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]-=i;
		b[i]=a[i];
	}
	sort(b+1, b+n+1);
	int m=unique(b+1, b+n+1)-b-1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			f[i][j]=f[i-1][j]+abs(a[i]-b[j]);
			if (j>1)
			{
				if (f[i][j-1]<f[i][j])
					f[i][j]=f[i][j-1];
			}
		}
	printf("%I64d\n", f[n][m]);
	
	return 0;
}