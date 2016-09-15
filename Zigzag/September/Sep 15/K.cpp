#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		LL tmp=(LL)n*m;
		if (n>=2 && m>=2 && tmp%6==0)
			printf("Yes\n");
		else if (n>=3 && n%2==1 && m%6==0)
			printf("Yes\n");
		else if (m>=3 && n%6==0 && m%2==1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
