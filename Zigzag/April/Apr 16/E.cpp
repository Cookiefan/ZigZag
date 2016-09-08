#include <bits/stdc++.h>
#define maxn 220
using namespace std;

int n,m,k;
int f[maxn][maxn], a[maxn], s[maxn];

int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	scanf("%d%d",&n,&k);
	m=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		m=max(m,s[i]);
		for (int j=1;j<=s[i];j++)
			scanf("%d",&a[j]);
		for (int j=1;j<=s[i];j++)
			f[i][j]=a[j];
	}
	for (int i=1;i<=n;i++)
		for (int j=s[i]+1;j<=m;j++) f[i][j]=50;
	int sum=0;
	for (int j=1;j<=m;j++)
		for (int i=1;i<=n;i++)	
			if (f[i][j]>=sum && k)
			{
				//cout<<f[i][j]<<endl;
				sum+=f[i][j];
				k--;
			}
	while (k)
	{
		sum+=50;
		k--;
	}
	printf("%d\n",sum);
	return 0;
}