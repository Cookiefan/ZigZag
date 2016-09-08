#include <bits/stdc++.h>
using namespace std;

int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int ans=1;
		for (int i=1;i<=n;i++)
			ans*=26;
		for (int i=1;i<=m;i++)
			ans*=10;
		if (n+m) cout<<ans<<endl;
		else cout<<0<<endl;
	}

	return 0;
}