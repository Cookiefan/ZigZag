#include <bits/stdc++.h>
using namespace std;
int a,b;

int main()
{
	int x,n;
	scanf("%d",&n);
	a=b=0;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		a|=x;
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		b|=x;
	}
	printf("%d\n",a+b);
	return 0;
}