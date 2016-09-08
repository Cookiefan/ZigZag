#include <bits/stdc++.h>
#define pi acos(-1.0)
using namespace std;
int n,m;
double len;

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%lf",&len);
	double ans=0, th=pi*(n-2)/n;
	for (int i=0;i<m;i++)
	{
		ans+=len*(n-0.5);
		len=0.5*len*sqrt(2.0*(1.0-cos(th)));
	}
	ans+=len*(n*1.0-1.0);
	printf("%.5f\n",ans);

	return 0;
}