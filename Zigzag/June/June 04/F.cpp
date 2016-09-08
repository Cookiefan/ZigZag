#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, x, a=0, b=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if (x&1) a++;
		else b++;
	}
	printf("%d %d\n",a,b);
	return 0;
}