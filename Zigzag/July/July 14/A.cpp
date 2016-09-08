#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int n;
int a[maxn];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	if (n==1)
	{
		if (a[1]==1) printf("YES\n");
		else printf("NO\n");
	}
	else
	{
		int sum=0;
		for (int i=1;i<=n;i++) sum+=a[i];
		if (sum==n-1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}