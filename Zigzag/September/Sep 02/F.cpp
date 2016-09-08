#include <bits/stdc++.h>
#define maxn 100200
using namespace std;
int a[maxn];
int lf[maxn], rt[maxn];
int n;

bool judge()
{
	memset(lf,0,sizeof(lf));
	memset(rt,0,sizeof(rt));
	for (int i=1;i<=n;i++)
	{
		if (i==1) lf[i]=1;
		else if (a[i-1]<=a[i]) lf[i]=lf[i-1]; else lf[i]=0;
	}
	for (int i=n;i>=1;i--)
	{
		if (i==n) rt[i]=1;
		else if (a[i]<=a[i+1]) rt[i]=rt[i+1]; else rt[i]=0;
	}
	int ans=(rt[2] || lf[n-1]);
	for (int i=2;i<n;i++)
		if (lf[i-1] && rt[i+1] && a[i-1]<=a[i+1]) ans=1;
	return ans;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		int ans=0;
		ans|=judge();
		for (int i=1;i<=n/2;i++) swap(a[i], a[n-i+1]);
		ans|=judge();
		printf(ans?"YES\n":"NO\n");
	}
	return 0;
}