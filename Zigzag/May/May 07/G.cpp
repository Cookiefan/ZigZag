#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int a[maxn];
int v[maxn];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1, a+n+1);
	memset(v,0,sizeof(v));
	int  sum=0, ans=0;
	while (sum<n)
	{
		int last=0;
		for (int i=1;i<=n;i++)
			if (!v[i] && a[i]>last)
			{
				last=a[i];
				v[i]=1;
				sum++;
			}
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}