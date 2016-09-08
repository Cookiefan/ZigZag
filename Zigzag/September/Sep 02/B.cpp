#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

int n;

//欧拉函数
ULL phi(ULL x)
{
	ULL cnt=x;
	for (ULL i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x>1) cnt=cnt/x*(x-1);
	return cnt;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		ULL tmp=0, ans=0;
		for (int m=1;m*m<=n;m++)
			if (n%m==0)
			{
				tmp+=n;
				ans+=(ULL)m*m;
				if (m*m<n)
				{
					tmp+=n;
					ans+=(ULL)(n/m)*(n/m);
				}
			}
		ans-=tmp;
		printf("%I64u\n", ans);
	}
	
	return 0;
}