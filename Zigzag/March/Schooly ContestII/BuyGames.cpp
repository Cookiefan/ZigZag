#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,m,k;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&k);
		int l=(1+k)*k/2, r=(n-k+1)*n/2;
		if (m<l || m>r)
		{
			printf("No\n");
			continue;
		}
		int fir=1+(r-l)/k;
		

	}
	
	return 0;
}