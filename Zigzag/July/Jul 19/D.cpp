#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

typedef long long llg;
llg a[maxn];
map<llg , llg> mp;
vector<llg> g[maxn], p[maxn], sum[maxn];
int n,m;

llg gcd(llg a, llg b)
{
	return (!a)?b:gcd(b%a, a);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%I64d",&a[i]);
		mp.clear();
		for (int i=1;i<=n;i++)
		{
			g[i].clear();
			p[i].clear();
			sum[i].clear();
			g[i].push_back(a[i]);
			p[i].push_back(i);
			sum[i].push_back(1);
			if (mp.find(a[i])==mp.end()) mp[a[i]]=0;
			mp[a[i]]++;
			int ss=g[i-1].size();
			for (int k=0;k<ss;k++)
			{
				llg tmp=gcd(g[i-1][k], a[i]);
				if (tmp!=g[i].back())
				{
					g[i].push_back(tmp);
					p[i].push_back(p[i-1][k]);
					sum[i].push_back(sum[i-1][k]);
				}
				else
				{
					p[i][p[i].size()-1]=p[i-1][k];
					sum[i][sum[i].size()-1]+=sum[i-1][k];
				}
				if (mp.find(tmp)==mp.end()) mp[tmp]=0;
				mp[tmp]+=sum[i-1][k];
			}
		}
		scanf("%d",&m);
		int l, r;
		printf("Case #%d:\n",o);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&l, &r);
			int ss=g[r].size();
			llg ans;
			for (int k=0;k<ss;k++)
				if (p[r][k]<=l)
				{
					ans=g[r][k];
					break;
				}
			printf("%I64d %I64d\n",ans, mp[ans]);
		}
	}
	return 0;
}