#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
int n;
int a[maxn];


int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	if (a[n]-a[1]+1<a[1]+a[2])
	{
		printf("YES\n");
		printf("%d\n", a[n]-a[1]+1);
	}
	else
		printf("NO\n");
	
	return 0;
}