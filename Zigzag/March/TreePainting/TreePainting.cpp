#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
int dg[maxn];
int n;

int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int x,y;
		int ans=0;
		memset(dg,0,sizeof(dg));
		for (int i=2;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			dg[x]++; dg[y]++;
		}
		ans+=(dg[1]+1)/2;
		for (int i=2;i<=n;i++)
			ans+=(dg[i]-1)/2;
		cout<<ans<<endl;
	}
	return 0;
}