#include <bits/stdc++.h>
#define maxn 1200
int a[maxn];
int n,m;

int gcd(int a, int b)
{
	return (!a)?b:gcd(b%a, a);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		int x,y;
		scanf("%d%d",&n,&m);
		memset(a,-1,sizeof(a));
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			a[x]=y;
		}
		a[n+1]=0;
		for (int i=n;i>=3;i--)
			if (a[i]==-1)
				a[i]=a[i+1];
		if (a[1]==-1) a[1]=100;
		if (a[2]==-1) a[2]=a[1];
		int up=a[1]+a[2], dw=0;
		for (int i=1;i<=n;i++) dw+=a[i];
		printf("%d/%d\n",up/gcd(up,dw),dw/gcd(up,dw));
	}

	return 0;
}