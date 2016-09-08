#include <bits/stdc++.h>
using namespace std;
int n,m;

int main()
{
	char c;
	scanf("%d%d",&n,&m);
	int flag=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&c);
			if (!(c=='W' || c=='B' || c=='G'))
				flag=0;
		}
	printf(flag?"#Black&White\n":"#Color\n");

	return 0;
}