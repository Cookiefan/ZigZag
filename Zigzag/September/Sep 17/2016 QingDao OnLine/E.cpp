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
		if (n&1) printf("Balanced\n");
		else printf("Bad\n");
	}
	return 0;
}