#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

long long gcd(long long a,long long b)
{
    return (b==0?a:gcd(b, a%b));
}

long long phi(long long x)
{
	long long cnt=x;
	for (long long i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x>1) cnt=cnt/x*(x-1);
	return cnt;
}

int n,m;

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		long long ans=0;
		for (int i=1;i<=2016;i++)
			if (2016%i==0)
				ans+=(long long)(m*i*phi(n/i))/2016;
		printf("%I64d\n",ans);
	}

	return 0;
}