#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 220000
using namespace std;

struct con
{
	int s,a,id;
	friend bool operator <(con a, con b)
	{
		return (a.s==b.s)?(a.id<b.id):(a.s>b.s);
	}
}p[maxn],l[5][maxn];
int n,m,q;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&q);
		for (int i=1;i<=2*n;i++)
			p[i].id=i;
		for (int i=1;i<=2*n;i++)
			scanf("%d",&p[i].s);
		for (int i=1;i<=2*n;i++)
			scanf("%d",&p[i].a);

		sort(p+1,p+2*n+1);
		for (int t=1;t<=m;t++)
		{
			for (int i=1;i<2*n;i+=2)
			{
				p[i+(p[i].a<p[i+1].a)].s++;
				l[1][(i+1)/2]=p[i+(p[i].a<p[i+1].a)];
				l[2][(i+1)/2]=p[i+(p[i].a>p[i+1].a)];
			}
			int i=1,j=1,now=0;
			while (i<=n || j<=n)
			{
				if ((j==n+1) || (i<=n && l[1][i]<l[2][j])) p[++now]=l[1][i++];
				if ((i==n+1) || (j<=n && l[2][j]<l[1][i])) p[++now]=l[2][j++];
			}
		}
		printf("%d\n",p[q].id);
	}
	return 0;
}