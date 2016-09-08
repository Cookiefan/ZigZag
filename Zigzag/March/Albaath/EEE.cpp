#include <bits/stdc++.h>
#define oo 1000000007
#define maxn 420000
using namespace std;

typedef long long llg;

llg frac[maxn],inv_frac[maxn];

llg inv(llg x)
{
	if (x==1) return 1;
	else return (oo-oo/x)*inv(oo%x)%oo;
}

llg com(llg n, llg m)
{
	return (frac[n]*inv_frac[m]%oo)*inv_frac[n-m]%oo;
}

llg get_ans(llg n, llg m)
{
	return com(n+m,n);
}
int main()
{
	frac[0]=1;
	inv_frac[0]=1;
	for (int i=1;i<=200002;i++)
	{
		frac[i]=frac[i-1]*i%oo;
		inv_frac[i]=inv(frac[i]);
	}
	int Case;
	scanf("%d",&Case);
	int n,m,x,y;
	for (int o=1;o<=Case;o++)
	{
		// n=100000; m=100000;
		scanf("%d%d",&n,&m);
		n--; m--;
		// x=50000; y=50000;
		scanf("%d%d",&x,&y);
		x--; y--;
		llg ans=(get_ans(n,m)-get_ans(x,y)*get_ans(n-x,m-y)%oo+oo)%oo;
		printf("%I64d\n",ans);
	}
	
	return 0;
}