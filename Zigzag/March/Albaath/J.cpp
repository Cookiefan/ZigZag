#include <bits/stdc++.h>
#define maxn 22000
using namespace std;
int n,p,q,a,b;
long long x[maxn];

bool judge(int len)
{
	a=b=0;
	long long now=0;
	for (int i=1;i<=n;i++)
		if (now<x[i])
		{
			a++;
			now=(long long) x[i]+len-1;
		}
	now=0;
	for (int i=1;i<=n;i++)
		if (now<x[i])
		{
			b++;
			now=(long long) x[i]+2*len-1;
		}
	return (p+q>=a || (p+q>=b && (q>=a-b || (p-2*b+a)/2+q>=a-b ) ) );
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&p,&q);
		for (int i=1;i<=n;i++)
			scanf("%I64d",&x[i]);
		sort(x+1,x+n+1);
		int l=1,r=1000000001,ans;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (judge(mid))
			{
				r=mid-1;
				ans=mid;
			}
			else
				l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}