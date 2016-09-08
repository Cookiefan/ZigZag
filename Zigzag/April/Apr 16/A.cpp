#include <bits/stdc++.h>
#define maxn 2200000
using namespace std;
int r[maxn],c[maxn];
long long zr,zc,sr,sc;
long long n;
int m;

int main()
{
	freopen("adjustment.in","r",stdin);
	freopen("adjustment.out","w",stdout);
	scanf("%I64d%d",&n,&m);
	memset(r,0,sizeof(r));
	memset(c,0,sizeof(c));
	sr=sc=n*(n+1)/2;
	zr=zc=n;
	char sign;
	long long x;
	for (int i=1;i<=m;i++)
	{
		scanf(" %c %I64d",&sign,&x);
		if (sign=='R')
		{
			if (r[x])
			{
				printf("0\n");
			}
			else
			{
				long long ans=zr*x+sr;
				printf("%I64d\n",ans);
				r[x]=1;
				zc--;
				sc-=x;
			}
		}
		else
		{
			if (c[x])
			{
				printf("0\n");
			}
			else
			{
				long long ans=zc*x+sc;
				printf("%I64d\n",ans);
				c[x]=1;
				zr--;
				sr-=x;
			}
		}
	}	
	return 0;
}