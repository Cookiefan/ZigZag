#include <bits/stdc++.h>
#define maxn 220000
#define oo 1000000007
using namespace std;
typedef long long LL;
int t[maxn];
int vis[maxn], step[maxn];
int n, tmp, sum, num;
LL ans;

LL exp(LL a, LL b, LL p)
{
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

void dfs(int x, int i, int k)
{
	vis[x]=i;
	step[x]=k;
	if (!vis[t[x]]) dfs(t[x], i, k+1);
	else if (vis[t[x]]==i) tmp=k-step[t[x]]+1;
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&t[i]);
	sum=n;
	ans=1;
	for (int i=1;i<=n;i++)
		if (!vis[i])
		{
			tmp=0;
			dfs(i, i, 0);
			if (tmp>=2)
			{
				ans=ans*(exp(2, tmp, oo)-2+oo)%oo;
				sum-=tmp;
			}
		}
	ans=ans*exp(2, sum, oo)%oo;
	printf("%I64d\n",ans);
	return 0;
}