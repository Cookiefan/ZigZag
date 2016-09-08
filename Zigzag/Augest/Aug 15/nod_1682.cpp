#include <bits/stdc++.h>
#define maxn 8800
using namespace std;
int l[maxn], h[maxn];
int a[maxn], ans[maxn];
int n;


int main()
{
	int n ;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		memset(l,0,sizeof(l));
		memset(h,0,sizeof(h));
		int now=0;
		for (int j=i;j>=1;j--)
		{
			if (a[j]<a[i]) now--;
			else if (a[j]>a[i]) now++;
			if (now<0) l[0-now]++;
			else h[now]++;
		}
		now=0;
		for (int j=i;j<=n;j++)
		{
			if (a[j]<a[i]) now--;
			else if (a[j]>a[i]) now++;
			if (now<=0) ans[i]+=h[0-now];
			else ans[i]+=l[now];
		}
	}
	for (int i=1;i<=n;i++)
		printf(i<n?"%d ":"%d\n",ans[i]);

	return 0;
}