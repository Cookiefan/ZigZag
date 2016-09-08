#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int a[maxn][maxn];
int w[maxn], h[maxn];
int n,m,sum;
int x,y;
char c;

int main()
{
	scanf("%d%d ",&n,&m);
	memset(w,0,sizeof(w));
	memset(h,0,sizeof(h));
	sum=0, x=0, y=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&c);
			if (c=='*')
			{
				a[i][j]=1;
				w[i]++;
				h[j]++;
				sum++;
			}
			else
				a[i][j]=0;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if ((a[i][j]==0 && w[i]+h[j]==sum) || (a[i][j]==1 && w[i]+h[j]-1==sum))
			{
				x=i;
				y=j;
				break;
			}
	if (!x && !y) printf("NO\n");
	else
	{
		printf("YES\n");
		printf("%d %d\n",x, y);
	}
	return 0;
}