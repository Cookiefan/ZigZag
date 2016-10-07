#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

#define inf 9999999
#define maxn 2020
typedef long long LL;
int ax[maxn], ay[maxn];
LL s[maxn][maxn];
vector<int> sum[maxn*2];
int n,m,p,mx,my;

LL getsum(int u, int v, int x, int y)
{
	x=min(x, mx); y=min(y, my);
	return s[x][y]-s[u-1][y]-s[x][v-1]+s[u-1][v-1];
}

int query(int x, int y)
{
	int l=1, r=max(mx, my),tmp=inf;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if (getsum(x,y,x+mid,y+mid)>0)
		{
			tmp=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	return tmp;
}

int main()
{
	//freopen("I.in","r",stdin);
	scanf("%d%d%d",&n,&m,&p);
	mx=0, my=0;
	for (int i=0;i<n;i++)
	{
		scanf("%d",&ax[i]);
		ax[i]++;
		mx=max(mx, ax[i]);
	}
	for (int i=0;i<m;i++)
	{
		scanf("%d",&ay[i]);
		ay[i]++;
		my=max(my, ay[i]);
	}
	memset(s,0,sizeof(s));
	int x, y;
	for (int i=0;i<p;i++)
	{
		scanf("%d%d",&x,&y);
		x++; y++;
		s[x][y]=1;
	}
	for (int i=1;i<=mx;i++)
		for (int j=1;j<=my;j++)
			s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+s[i][j];

	for (int i=0;i<=mx+my;i++) sum[i].clear();
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			x=ax[i],y=ay[j];
			sum[y-x+mx].push_back(x+y);
		}
	for (int i=0;i<=mx+my;i++)
		sort(sum[i].begin(), sum[i].end());
	LL ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			x=ax[i], y=ay[j];
			int tmp=query(x, y);
			int id=y-x+mx;
			int k=lower_bound(sum[id].begin(), sum[id].end(), x+tmp+y+tmp)-sum[id].begin();
			ans+=(sum[id].size()-k);
		}
	printf("%lld\n",ans);
	return 0;
}