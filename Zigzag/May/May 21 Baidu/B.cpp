#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define inf 1999999999
using namespace std;

int f[18][18][80000];
int cnt[80000];
int num[18], v[18];
int n,mxm;

int position(int x, int k)
{
	if (k==0) return 1;
	return (x>>(k-1)) & 1;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int p;
		for (int i=1;i<=n;i++) v[i]=-1;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&num[i],&p); p++;
			v[p]=i;
		}
		mxm=(1<<n)-1;
		for (int i=0;i<mxm;i++)
		{
			cnt[i]=0;
			int x=i;
			while (x)
			{
				cnt[i]+=x&1;
				x>>=1;
			}
		}
		for (int i=0;i<=n;i++)
			for (int j=0;j<=n;j++)
				for (int k=0;k<=mxm;k++)
					f[i][j][k]=-inf;
		num[0]=0;
		f[0][0][0]=0;
		int ans=-inf;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) if (v[i]==-1 || j==v[i])
				for (int mask=0;mask<=mxm;mask++)
					if (cnt[mask]==i-1 && position(mask, j)==0)
					{
						for (int k=0;k<=n;k++)
							if (f[i-1][k][mask]!=-inf && position(mask, k)==1)
							{
								//cout<<i-1<<' '<<k<<' '<<mask<<' '<<f[i-1][k][mask]+num[k]*num[j]<<"->"<<i<<' '<<j<<' '<<(mask|(1<<(j-1)))<<' '<<f[i][j][mask|(1<<(j-1))]<<endl;
								f[i][j][mask|(1<<(j-1))]=max(f[i][j][mask|(1<<(j-1))] , f[i-1][k][mask]+num[k]*num[j]);
							}
						if (i==n)
							ans=max(ans, f[i][j][mask|(1<<(j-1))]);
					}
		printf("Case #%d:\n",o);
		printf("%d\n",ans);
	}
	return 0;
}