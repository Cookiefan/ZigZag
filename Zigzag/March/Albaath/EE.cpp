#include <bits/stdc++.h>
#define oo 1000000007
using namespace std;

typedef long long LL;

//快速幂
LL Power(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

//Lucas定理(求组合数取模,注意p<=10^5)
LL com(LL n,LL m,LL p)
{
	if (m>n) return 0;
	LL ans=1;
	for (int i=1;i<=m;i++)
	{
		ans=ans*(n-i+1)%p;
		ans=ans*Power(i,p-2,p)%p;
	}
	return ans;
}
	
LL lucas(LL n,LL m,LL p)
{
	if (m==0) return 1;
	return (com(n%p,m%p,p)*lucas(n/p,m/p,p))%p;
}

LL get_ans(LL n, LL m)
{
	return lucas(n+m,n,oo);
}

int main()
{
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
		LL ans=(get_ans(n,m)-get_ans(x,y)*get_ans(n-x,m-y)%oo+oo)%oo;
		printf("%I64d\n",ans);
	}
	
	return 0;
}