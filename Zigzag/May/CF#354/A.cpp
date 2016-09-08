#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int a[maxn], v[maxn];
int main()
{
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		v[a[i]]=i;
	}
	if ((v[1]==1 && v[n]==n) || (v[n]==1 && v[1]==n))
		printf("%d\n",n-1);
	else
		printf("%d\n", max(max(n-v[1], n-v[n]), max(v[1]-1, v[n]-1)));
	return 0;
}