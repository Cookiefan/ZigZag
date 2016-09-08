#include <bits/stdc++.h>
using namespace std;

double a,b;

int main()
{
	while (scanf("%lf%lf",&a,&b)!=EOF)
	{
		printf("%.8lf %.8lf\n",2.0*a*b,4.0*a*a/(a*a+b*b)*b*b);	
	}
	return 0;
}