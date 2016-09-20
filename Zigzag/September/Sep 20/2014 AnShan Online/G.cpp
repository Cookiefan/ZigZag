#include <bits/stdc++.h>
#define maxn 102
using namespace std;
//快速幂
double exp(double a, int b)
{
	double tmp=1;
	while (b)
	{
		if (b&1) tmp=tmp*a;
		a=a*a;
		b=b/2;
	}
	return tmp;
}

int n;
int a[maxn];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1, a+n+1, greater<int>());
		double tmp=1, ans=0;
		for (int i=1;i<=n;i++)
		{
			ans+=tmp*a[i];
			tmp=tmp*0.95;
		}
		printf("%.6f\n",ans);
	}
	return 0;
}
