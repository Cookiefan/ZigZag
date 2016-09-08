#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long llg;
llg p, q, a, b;
int n;

llg mul(llg a,llg b,llg p)
{
	a%=p,b%=p;
	llg tmp=0;
	while (b)
	{
		if (b&1) tmp=(tmp+a)%p;
		a=(a+a)%p;
		b/=2;
	}
	return tmp;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%I64d%I64d",&q,&p);
		if ((q-1)%2==0)
		{
			a=(q-1)/2;
			b=q-2;
		}
		else 
		{
			a=q-1;
			b=(q-2)/2;
		}
		printf("%I64d\n",mul(a, b, p));
	}
	return 0;
}