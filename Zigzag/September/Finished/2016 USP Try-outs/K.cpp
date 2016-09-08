#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	scanf("%d",&n);
	double tmp=1, cnt=1;
	for (int i=1;i<=n+1;i++)
	{
		tmp=tmp*(n-i+1);
		cnt=cnt*n;
		if (tmp/cnt<0.5)
		{
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}