#include <bits/stdc++.h>
#define maxn 1020
using namespace std;
typedef long long LL;
const LL oo=105225319;
int b[maxn][12], pt[12];

LL dp[maxn][maxn];
int l[maxn], r[maxn];
int nxt[maxn][12];
int sz[maxn];

vector<int>mo[maxn];
int n, m;
LL ans;

int main()
{
	for (int msk=0;msk<(1<<10);msk++)
		for (int i=0;i<10;i++)
			if ((msk>>i)&1)
				b[msk][i]=1;
	for (int i=0;i<10;i++) pt[i]=1<<i;

	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&l[i]);
		for (int i=1;i<=n;i++) scanf("%d",&r[i]);
		memset(nxt,-1,sizeof(nxt));
		memset(sz,0,sizeof(sz));
		m=0;
		for (int i=1;i<=n;i++) mo[i].clear();
		for (int i=1;i<=n;i++)
		{
			if (r[i]-l[i]+1==n) 
			{
				m++;
				continue;
			}
			for (int j=l[i];j<=r[i];j++)
			{
				mo[j].push_back(i);
				sz[j]++;
				if (j>l[i]) nxt[j-1][mo[j-1].size()-1]=mo[j].size()-1;
			}
		}
		for (int i=1;i<=n;i++) if (sz[i]>10)
		{
			printf("0\n");
			continue;
		}
		memset(dp,0,sizeof(dp));
		dp[1][0]=1;
		for (int msk=1;msk<(1<<sz[1]);msk<<=1)
			dp[1][msk]=1;
		for (int i=1;i<n;i++)
			for (int msk=0;msk<(1<<sz[i]);msk++)
			{
				if (!dp[i][msk]) continue;
				int tmp=0, flag=1;
				for (int j=0;j<sz[i];j++)
				{
					if (!b[msk][j] && nxt[i][j]==-1)
						flag=0;
					if (b[msk][j] && nxt[i][j]!=-1)
						tmp|=pt[nxt[i][j]];
				}
				if (!flag) continue;
				(dp[i+1][tmp]+=dp[i][msk])%=oo;
				for (int j=0;j<sz[i+1];j++)
					if (!b[tmp][j])
						(dp[i+1][tmp|pt[j]]+=dp[i][msk])%=oo;
			}
		ans=dp[n][(1<<sz[n])-1];
		//cout<<ans<<endl;
		for (int i=1;i<=m;i++)
			(ans*=i)%=oo;
		printf("Case #%d: %I64d\n",o,ans);
	}

	return 0;
}