#include <bits/stdc++.h>
using namespace std;
int a[100];

int main()
{
	freopen("I.in","r",stdin);
	int n;
	while (scanf(" %d",&n)!=EOF)
	{
		int x, y;
		char c;
		for (int i=1;i<=n;i++) a[i]=n;
		for (int i=1;i<n;i++)
		{
			scanf("%d %c %d",&x, &c, &y);
			if (c=='+')
				a[n+i]=a[x]+a[y];
			else if (c=='-')
				a[n+i]=a[x]-a[y];
			else if (c=='*')
				a[n+i]=a[x]*a[y];
			else 
				a[n+i]=a[x]/a[y];
		}
		cout<<n<<endl;
		if (a[n+n-1]==24)
			printf("Yes\n"); else printf("No\n");
	}
	return 0;
}