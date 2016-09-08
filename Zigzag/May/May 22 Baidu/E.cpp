#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define oo 1000000007
#define maxn 220000

using namespace std;

struct seg
{
	int l, r;
	friend bool operator < (seg a, seg b)
	{
		return a.r>b.r;
	};
};

bool cmp(seg a, seg b)
{
	return a.l<b.l;
}
priority_queue<seg> q;

int n,m,k, ll, rr;
int v[maxn];
long long sum[maxn];
seg s[maxn];
long long ans;

int main()
{
	while (scanf("%d%d%d",&n,&k,&m)!=EOF)
	{
		memset(sum,0,sizeof(sum));
		for (int i=1;i<=n;i++) scanf("%d", &v[i]), sum[i]=sum[i-1]+v[i];
		for (int i=1;i<=m;i++) scanf("%d%d", &s[i].l, &s[i].r);
		sort(s+1, s+m+1, cmp);
		while (!q.empty()) q.pop();
		ans=0;
		for (int i=1;i<=m;i++)
		{
			//cout<<s[i].l<<' '<<s[i].r<<' ';
			if (q.size()==k) q.pop();
			q.push(s[i]);
			ll=s[i].l;
			rr=q.top().r;
			//cout<<ll<<' '<<rr<<endl;
			if (q.size()==k && ll<=rr) ans=max(ans, sum[rr]-sum[ll-1]);
		}
		printf("%I64d\n",ans);
	}

	return 0;
}