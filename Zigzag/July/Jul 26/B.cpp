#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int c[maxn];
int n;
double ans;

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		ans=0;
		for (int i=1;i<=n;i++) scanf("%d",&c[i]);
		ans+=(double)(c[1]+c[n])*0.5;
		for (int i=2;i<n;i++)
			ans+=(double)c[i]/3;
		printf("%.6f\n",ans);
	}
	return 0;
}