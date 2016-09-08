#include <bits/stdc++.h>
#define maxn 520
using namespace std;

long long a[maxn][maxn];
int n, x, y, m;
long long sum, tmp;
long long sx[maxn], sy[maxn];
long long ss, st;

bool judge()
{
	memset(sx,0,sizeof(sx));
	memset(sy,0,sizeof(sy));
	ss=st=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (i==j) ss+=a[i][j];
			if (i+j==n+1) st+=a[i][j];
			sx[i]+=a[i][j];
			sy[j]+=a[i][j];
		}
	for (int i=1;i<=n;i++) if (sx[i]!=sum) return 0;
	for (int j=1;j<=m;j++) if (sy[j]!=sum) return 0;
	if (ss!=sum) return 0;
	if (st!=sum) return 0;
	return 1;
}

int main()
{
	scanf("%d",&n);
	m=n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{	
			scanf("%d",&a[i][j]);
			if (a[i][j]==0) x=i, y=j;
		}
	sum=tmp=0;
	for (int i=1;i<=n;i++)
	{
		if (i==x)
			for (int j=1;j<=m;j++) tmp+=a[i][j];
		else
		{
			sum=0;
			for (int j=1;j<=m;j++) sum+=a[i][j];
		}
	}
	a[x][y]=sum-tmp;
	// cout<<sum<<' '<<tmp<<endl;
	// cout<<a[x][y]<<endl;
	if (n==1)
		printf("1\n");
	else if (a[x][y]>0 && judge())
		printf("%I64d\n",a[x][y]);
	else
		printf("-1\n");
	return 0;

}