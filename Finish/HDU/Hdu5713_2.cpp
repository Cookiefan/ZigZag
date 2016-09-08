#include <bits/stdc++.h>
#define maxn 32000
#define oo 1000000009
using namespace std;

long long cnt[maxn], f[maxn][20], edges[maxn][20], tp[20];
int a[20][20];
int n,m,k,mxbit;

int main()
{
	int Case;
	scanf("%d",&Case);
	tp[0]=1;
	for (int i=1;i<=16;i++) tp[i]=tp[i-1]*2;
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&k);
		memset(a,0,sizeof(a));
		for (int i=1;i<=m;i++)
		{
			int x, y;
			scanf("%d%d",&x,&y);
			a[x][y]=a[y][x]=1;
		}

		mxbit=(1<<n)-1;
		memset(edges,0,sizeof(edges));
		for (int mask=1;mask<=mxbit;mask++)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					if ((mask>>(j-1))&1)
						(edges[mask][i]+=a[i][j])%=oo;

		memset(cnt,0,sizeof(cnt));
		for (int i=1;i<=n;i++) cnt[1<<(i-1)]=1+a[i][i];
		for (int i=2;i<=n;i++)
		{
			int mask=(1<<i)-1;
			while(mask<(1<<n))
			{//枚举大小为i的集合
				int x=mask&-mask,y=mask+x;
				int t=(int)log2(x)+1;
				int tmp=mask-x, p=mask;
				do
				{//枚举包含最低位的子集p和包含次低位的子集mask-p
					if ((p & x) >0 && ((mask-p) & (tmp & -tmp)) >0)
						(cnt[mask]+=cnt[p]*cnt[mask-p]%oo*(tp[edges[mask-p][t]]-1)%oo)%=oo;
					p=(p-1)&(mask);
				}while (p!=mask);
				mask=((mask & ~y)/x >>1)|y;
			}
		}
		memset(f,0,sizeof(f));
		for (int i=1;i<=mxbit;i++)
			f[i][1]=cnt[i];
		for (int j=2;j<=k;j++)
			for (int i=j;i<=n;i++)
			{
				int mask=(1<<i)-1;
				while (mask<(1<<n))
				{//枚举大小为i的集合
					int x=mask&-mask,y=mask+x;
					int p=mask;
					do//枚举包含最低位mask的子集p
					{
						if ((p & x) >0)
							(f[mask][j]+=f[mask-p][j-1]*cnt[p]%oo)%=oo;
						p=(p-1)&mask;
					} while (p!=mask);
					mask=((mask & ~y)/x >>1)|y;
				}
			}
		printf("Case #%d:\n%d\n",o,f[(1<<n)-1][k]);
	}
	return 0;
}
/*
100
5 5 3
1 2
2 3
3 4
4 5
5 1
ans:10
*/