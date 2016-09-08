#include <bits/stdc++.h>
using namespace std;
long long x,g,y,r;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%I64d%I64d%I64d%I64d",&x,&g,&y,&r);
		long long m=g+y+r;
		x=x%m;
		if (0<=x && x<g) printf("GREEN\n");
		else if (g<=x && x<g+y) printf("YELLOW\n");
		else printf("RED\n");
	}
	
	return 0;
}