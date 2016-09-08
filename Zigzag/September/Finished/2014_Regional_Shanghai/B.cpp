#include <bits/stdc++.h>
#define maxn 2200200
using namespace std;

int n,m,p;
long long a[maxn], d[maxn];

int id(int x, int y)
{
	if (x<=0 || y<=0 || x>n || y>m) return 0; 
	return (x-1)*m+y;
}

void add_key(int xo, int yo, int xe, int ye, int z)
{
	d[id(xo, yo)]+=z;
	d[id(xo, ye+1)]-=z;
	d[id(xe+1, yo)]-=z;
	d[id(xe+1, ye+1)]+=z;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&p);
		memset(d,0,sizeof(d));
		memset(a,0,sizeof(a));
		char sign;
		int xo=1, yo=1, xe=1, ye=1, t;
		for (int i=1;i<=p;i++)
		{
			scanf(" %c %d",&sign, &t);
			switch (sign)
			{
				case 'U':
					xe=xo-t;
					add_key(xe, ye, xo-1, m, 1);
					add_key(xe, 1, xo-1, yo-1, -1);
				break;
				case 'D':
					xe=xo+t;
					add_key(xo, 1, xe-1, ye-1, 1);
					add_key(xo, yo, xe-1, m, -1);
				break;
				case 'L':
					ye=yo-t;
					add_key(1, ye, xo-1, yo-1, 1);
					add_key(xe, ye, n, yo-1, -1);
				break;
				case 'R':
					ye=yo+t;
					add_key(xo, yo, n, ye-1, 1);
					add_key(1, yo, xe-1, ye-1, -1);
				break;
			}
			xo=xe; yo=ye;
		}
		long long ans=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				//cout<<a[id(i-1, j)]<<' '<<a[id(i, j-1)]<<' '<<a[id(i-1, j-1)]<<endl;
				a[id(i,j)]=a[id(i-1, j)]+a[id(i, j-1)]-a[id(i-1, j-1)]+d[id(i, j)];
				ans+=(a[id(i,j)]/4)*(a[id(i,j)]/4);
				//cout<<d[id(i, j)]<<' ';
			}
			//cout<<endl;
		}
		printf("Case #%d: %lld\n",o, ans);
	}
	return 0;
}