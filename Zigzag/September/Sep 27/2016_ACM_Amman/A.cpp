#include <bits/stdc++.h>
#define maxn 220
#define maxm 32000
#define oo 1000000007
using namespace std;
typedef long long LL;

int a[maxn], b[maxn];
LL f[maxm], g[maxm];
int n,m,k,w;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d%d",&n,&m,&k,&w);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		for (int i=1;i<=m;i++) scanf("%d",&b[i]);
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[0]=1;
		for (int i=1;i<=n;i++)
			for (int j=w;j>=a[i];j--)
				(f[j]+=f[j-a[i]])%=oo;
		g[0]=1;
		for (int i=1;i<=m;i++)
			for (int j=w;j>=b[i];j--)
				(g[j]+=g[j-b[i]])%=oo;
		LL ans=0;
		for (int i=0;i<=w;i++)
			if (abs(2*i-w)<=k)
				(ans+=(f[i]*g[w-i]%oo))%=oo;
		printf("%d\n",ans);
	}
	return 0;
}
