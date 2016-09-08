#include <bits/stdc++.h>
#define maxn 10200
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
LL f[5][maxn];

int l[maxn];
long long v[maxn];
int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		m*=2;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&l[i], &v[i]);
			l[i]*=2;
		}

		LL ans=0;
		for (int i=1;i<=n;i++) ans=max(ans, v[i]);

		memset(f,0,sizeof(f));
		for (int i=1;i<=n;i++)
			for (int j=m;j>=0;j--)
			{
				if (j>=l[i])
				{
					for (int k=0;k<=2;k++)
						f[k][j]=max(f[k][j], f[k][j-l[i]]+v[i]);
				}
				if (j>=l[i]/2)
				{
					for (int k=1;k<=2;k++)
						f[k][j]=max(f[k][j], f[k-1][j-l[i]/2]+v[i]);
				}
				for (int k=1;k<=2;k++)
					ans=max(ans, f[k][j]);
			}
		printf("Case #%d: %I64d\n",o,ans);
	}
	return 0;
}