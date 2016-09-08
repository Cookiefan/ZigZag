#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 120000
#define oo 1000000007
using namespace std;
typedef long long LL;
LL a[maxn];
LL n,k;


LL power(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b>>1;
	}
	return tmp;
}



int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%I64d%I64d",&n,&k);
		if (n<k*(k+1)/2) printf("-1\n");
		else
		{
			LL ans=1, sum=0, now=1;
			sum=k*(k+1)/2;
			while (n-sum>=k)
			{
				sum+=k;
				now+=1;
			}
			a[1]=now;
			for (int i=2;i<=k;i++)
				a[i]=a[i-1]+1;
			for (int i=k;i>=1;i--)
				if (sum<n)
				{
					a[i]++;
					sum++;
				}
				else
					break;
			for (int i=1;i<=k;i++)
				ans=ans*a[i]%oo;			
			printf("%I64d\n",ans);
		}
	}

	return 0;
}