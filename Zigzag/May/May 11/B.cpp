#include <bits/stdc++.h>
#define maxn 1200000
#define maxm 12000
using namespace std;

int a[2][maxn], p[2], c[maxn];
int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=2;i<=n;i+=2) a[0][i/2-1]=i;
	for (int i=1;i<=n;i+=2) a[1][i/2]=i;
	int t, x, now=1, nn=n/2;
	p[0]=p[1]=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&t);
		if (t==1)
		{
			scanf("%d",&x);
			p[0]=(p[0]-x/2+nn)%nn;
			p[1]=(p[1]-x/2+nn)%nn;
			if (abs(x)%2==1)
			{
				if (x>0)
					p[now^1]=(p[now^1]-1+nn)%nn;
				else
					p[now]=(p[now]+1)%nn;
				now=now^1;
			}
		}
		else
			now=now^1;
	}
	int k=p[now];
	for (int i=1;i<=n;i+=2) c[i]=a[now][k], k=(k+1)%nn;
	now=now^1; k=p[now];
	for (int i=2;i<=n;i+=2) c[i]=a[now][k], k=(k+1)%nn;
	for (int i=1;i<=n;i++)
		printf(i==n?"%d\n":"%d ",c[i]);
	return 0;
}