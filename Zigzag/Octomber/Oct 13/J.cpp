#include <bits/stdc++.h>
using namespace std;
#define maxn 500200
typedef unsigned int uit;
uit f[maxn], s[maxn];
int n;

int main()
{
	s[0]=0;
	for (int i=1;i<=500000;i++)
	{
		f[i]=0;
		for (int d=1;d*d<=i;d++)
			if (!(i%d))
			{
				f[i]=f[i]+((long long)(i/d)*(i/d+1)/2)*i;
				if (d*d==i) continue;
				int e=i/d;
				f[i]=f[i]+((long long)(i/e)*(i/e+1)/2)*i;
			}
		s[i]=s[i-1]+f[i];
	}
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		printf("Case #%d: %u\n",o,s[n]);
	}
	return 0;
}	