#include <bits/stdc++.h>
#define maxn 12000
using namespace std;

int f[maxn][2];
int a[maxn];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[0][0]=f[0][2]=0;
	for (int i=1;i<=n;i++)
	{
		f[i][0]=max(f[i-1][0], f[i-1][1]);
		f[i][1]=f[i-1][0]+a[i];
	}
	printf("%d\n",max(f[n][0], f[n][1]));
	return 0;
}