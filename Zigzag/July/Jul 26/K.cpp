#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
int n,m;
int x[maxn],y[maxn];
int v[maxn];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			scanf("%d%d",&x[i], &y[i]);
		if ((long long)n*(n-1)/2 > 2*m+1)
		{
			printf("YES\n");
			continue;
		}
		else
		{
			memset(v,0,sizeof(v));
			for (int i=1;i<=n;i++)
				for (int j=i+1;j<=n;j++)
					v[abs(x[i]-x[j])+abs(y[i]-y[j])]++;
			int ans=0;
			for (int i=0;i<=2*m;i++)
				if (v[i]>1)
				{
					ans=1;
					break;
				}
			if (ans==1) printf("YES\n");
			else printf("NO\n");
		}
	}


	return 0;
}
