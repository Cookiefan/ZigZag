#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
typedef long long LL;
int a[maxn], l[maxn], r[maxn];
LL sum[maxn];
int n,m,k;
typedef pair<int,int> pii;
pii seg[maxn];
priority_queue<int, vector<int>, greater<int> > q;

LL get_sum(int l, int r)
{
	return sum[r]-sum[l-1];
}

int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	int x,y;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		l[i]=x; r[i]=y;
		seg[i]=pii(x,i);
	}
	sort(seg+1, seg+m+1);
	while (!q.empty()) q.pop();
	LL ans=0;
	for (int i=1;i<=m;i++)
	{
		q.push(r[seg[i].second]);
		if (q.size()>k) q.pop();
		if (q.size()==k)
		{
			int now=q.top();
			ans=max(ans, get_sum(seg[i].first, now));	
		}
	}
	printf("%I64d\n",ans);

	return 0;
}