#include <bits/stdc++.h>
using namespace std;
long long a,b,c;
long long n;

int main()
{
	scanf("%d",&a);
	if (a<3) printf("-1\n");
	else if (a&1)
	{
		n=a/2;
		b=2*n*n+2*n;
		c=b+1;
		printf("%I64d %I64d\n",b,c);
	}
	else
	{
		n=a/2;
		b=n*n-1;
		c=n*n+1;
		printf("%I64d %I64d\n",b,c);
	}
	return 0;
}