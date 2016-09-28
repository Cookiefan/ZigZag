#include <bits/stdc++.h>
using namespace std;

int main()
{
	int Case;
	scanf("%d",&Case);
	int n;
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		printf("%d\n",n/5+(n%5>0));
	}
	return 0;
}