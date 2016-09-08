#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int a,b;
int n;

int main()
{
	int Case, x;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		a=b=0;
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			if (x==0) a=1;
			if (x==1) b=1;
		}
		printf((a&&b)?"YES\n":"NO\n");
	}
	return 0;
}