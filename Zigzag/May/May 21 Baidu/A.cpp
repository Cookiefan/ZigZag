#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define oo 1000000007

using namespace std;

int x,c,k;
long long m;
int v[12000];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		memset(v,0,sizeof(v));
		scanf("%d%I64d%d%d",&x,&m,&k,&c);
		int tmp=0, lp=0;
		long long p=0;
		while (p<m)
		{
			p++;
			tmp=(tmp*10+x)%k;
			if (!v[tmp]) v[tmp]=p;
			else
			{
				lp=p;
				break;
			}
		}
		printf("Case #%d:\n",o);
		if ((v[c]==m) || (v[c]!=0 && lp && m%lp==v[c])) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
