#include <bits/stdc++.h>
#define maxn 2020
#define oo 1000000007
using namespace std;
struct item
{
	int a,b;
	friend bool operator <(item x, item y)
	{
		return x.a>y.a;
	}
}s[maxn];
int f[maxn][maxn];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&s[i].a);
	for (int i=1;i<=n;i++)
		scanf("%d",&s[i].b);
	sort(s+1,s+n+1);
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i/2;j++)
			f[i][j]=max(f[i-1][j],f[i-1][j-1]+s[i].b);
	// for (int i=1;i<=n;i++)
	// {
	// 	for (int j=1;j<=n;j++)
	// 		cout<<f[i][j]<<' ';
	// 	cout<<endl;
	// }
	printf("%d\n",f[n][n/2]);

	return 0;
}