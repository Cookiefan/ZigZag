#include <bits/stdc++.h>
#define maxn 100200
#define oo 2000000000
using namespace std;
int n;
long long m;
int a[maxn];

bool count(long long x)//sum(<=x)
{
	long long tmp=0;
	for (int i=0, j=n-1;i<n;i++)
	{
		// while (j>0 && a[i]+a[j]>x) j--;
		// if (j<=i) break;
		// tmp+=(long long)(j-i);
		int l=0, r=i-1, cnt=-1;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (a[i]+a[mid]<=x)
			{
				cnt=mid;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		tmp+=cnt+1;
		if (tmp>=m) return 1;
	}
	return 0;
}

int main()
{
	//freopen("D.in","r",stdin);
	scanf("%d%I64d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	sort(a,a+n);
	long long l=0, r=a[n-1]+a[n-2];
	int ans=0;
	while (l<=r)
	{
		long long mid=(l+r)>>1;
		if (count(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}