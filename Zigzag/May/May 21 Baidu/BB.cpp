#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define inf 1999999999
using namespace std;

int f[18][80000];
int num[18], v[18], mx[80000], mi[80000];
int n,mxm;

int  count(int x)
{
	int tmp=0;
	while (x)
	{
		tmp+=x&1;
		x>>=1;
	}
	return tmp;
}

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
		mx[0]=mi[0]=0;
		for (int mask=1;mask<=mxm;mask++)
		{
			mx[mask]=-inf;
			mi[mask]=inf;
			for (int i=1;i<=n;i++)
			{
				if (position(mask, i)==1 && num[i]>mx[mask]) mx[mask]=num[i];
				if (position(mask, i)==1 && num[i]<mi[mask]) mi[mask]=num[i];
			}
		}
		for (int i=0;i<=n;i++)
			for (int k=0;k<=mxm;k++)
					f[i][k]=-inf;
		num[0]=0;
		f[0][0]=0;
		int ans=-inf;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) if (v[i]==-1 || j==v[i])
				for (int mask=0;mask<=mxm;mask++)
					if (count(mask)==i-1 && position(mask, j)==0 && f[i-1][mask]!=-inf)
					{
						int k;
						if (num[j]>=0) k=mx[mask]; else k=mi[mask];
						
						f[i][mask|(1<<(j-1))]=max(f[i][mask|(1<<(j-1))] , f[i-1][mask]+k*num[j]);
						cout<<i-1<<' '<<mask<<' '<<f[i-1][mask]+num[k]*num[j]<<"->"<<i<<' '<<(mask|(1<<(j-1)))<<' '<<f[i][mask|(1<<(j-1))]<<endl;
						if (i==n) ans=max(ans, f[i][mask|(1<<(j-1))]);
					}
		printf("Case #%d:\n",o);
		printf("%d\n",ans);
	}
	return 0;
}