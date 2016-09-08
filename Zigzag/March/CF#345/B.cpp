#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int a[maxn];
bool v[maxn];
int n;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	memset(v,0,sizeof(v));
	int now,ans=0,picked=0;
	while (picked<n)
	{
		for (int i=1;i<=n;i++)
			if (!v[i])
			{
				v[i]=1, now=a[i], picked++;
				break;
			}
		for (int i=1;i<=n;i++)
			if (!v[i] && a[i]>now)
				ans++, v[i]=1, now=a[i], picked++;
	}
	printf("%d\n",ans);
	return 0;
}