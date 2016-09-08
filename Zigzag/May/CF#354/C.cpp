#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
int a[maxn], s[maxn];
char c;
int n, k;

bool judge(int len)
{
	for (int i=1;i<=n-len+1;i++)
		if (s[i+len-1]-s[i-1]<=k || len-(s[i+len-1]-s[i-1])<=k)
			return 1;
	return 0;
}
int main()
{
	scanf("%d%d",&n,&k);
	s[0]=0;
	for (int i=1;i<=n;i++)
	{
		scanf(" %c",&c);
		if (c=='a') a[i]=1; else a[i]=0;
		s[i]=s[i-1]+a[i];
	}
	int l=1, r=n, ans;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (judge(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	printf("%d\n",ans);

	return 0;
}