#include <bits/stdc++.h>
#define inf 99999999
using namespace std;

int a[3200];
int n;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		for (int i=1;i<n;i++) scanf("%d",&a[i]);
		int x=inf, y=inf;
		for (int i=2;i<n;i++)
		{
			x=min(x, a[i]*(i-1)-a[i-1]*i);
			y=min(y, a[i-1]-a[i]);
		}
		printf("%d\n",-n*x-(2*n-2)*y);
	}

	return 0;
}