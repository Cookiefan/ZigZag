#include <bits/stdc++.h>
using namespace std;

int n,m;
int x,y;

int main()
{
	while (scanf("%d%d%d%d",&n,&m,&x,&y)!=EOF)
	{
		int ans, num=min(n,m);
		if (n==m && n%2==1 && x==y && x==n/2+1)
			ans=n/2;

		else
		{
			ans=(num+1)/2;
			ans=max(ans, min(x-1, min(y, m-y+1)));
			ans=max(ans, min(n-x, min(y, m-y+1)));
			ans=max(ans, min(y-1, min(x, n-x+1)));
			ans=max(ans, min(m-y, min(x, n-x+1)));
		}

		printf("%d\n",ans);
	}
	return 0;
	
}
