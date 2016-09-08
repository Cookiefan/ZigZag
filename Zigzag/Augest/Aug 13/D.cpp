#include <bits/stdc++.h>
#define maxn 5200
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
LL f[maxn];
pii g[maxn];

struct stick
{
	int l;
	long long v;
}a[maxn];

int n,m;

pii change(pii s, int x)
{
	pii t=s;
	if (x>=t.first)
	{
		t.second=t.first;
		t.first=x;
	}
	else if (x>t.second)
		t.second=x;
	return t;
}

int sum(pii s)
{
	return s.first+s.second;
}

bool cmp(stick a, stick b)
{
	return a.l>b.l;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d%d",&a[i].l, &a[i].v);
		sort(a+1, a+n+1, cmp);
		LL ans=0;
		for (int i=1;i<=n;i++) ans=max(ans, a[i].v);
		for (int i=0;i<=n;i++)
			for (int j=0;j<=2*m;j++)
			{
				f[j]=0;
				g[j]=pii(0,0);
			}
		for (int i=1;i<=n;i++)
			for (int j=2*m;j>=a[i].l;j--)
			{
				pii tmp=change(g[j-a[i].l], a[i].l);
				if (2*j-tmp.first-tmp.second<=2*m)
				{
					if (f[j]<f[j-a[i].l]+a[i].v || f[j]==f[j-a[i].l]+a[i].v && sum(tmp)>sum(g[j]))
					{
						f[j]=f[j-a[i].l]+a[i].v;
						g[j]=tmp;
					}
					ans=max(f[j], ans);
				}
			}
		printf("Case #%d: %I64d\n",o,ans);
	}
	return 0;
}