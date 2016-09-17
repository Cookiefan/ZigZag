#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL f[2000000];
LL v[200], w[200];
int n,m;
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		int flag=0;
		if (m>1000000) flag=1, m/=1000;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&w[i], &v[i]);
			if (flag) w[i]/=1000;
		}
		memset(f,0,sizeof(f));
		f[0]=0;
		for (int i=1;i<=n;i++)
			for (int j=m;j>=w[i];j--)
				f[j]=max(f[j], f[j-w[i]]+v[i]);
		LL ans=0;
		for (int i=0;i<=m;i++)
		{
			ans=max(ans, f[i]);
		}
		printf("%I64d\n", ans);

	}
	return 0;
}