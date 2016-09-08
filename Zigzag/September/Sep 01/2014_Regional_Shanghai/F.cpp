#include <bits/stdc++.h>
#define maxn 205
using namespace std;
typedef long long LL;
const LL oo=1e9+7;
LL f[22][maxn];
int c[maxn], sum[maxn];
LL frac[100050], revf[100050];
int n,m,k;

LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

LL Com(int n, int m)
{
	if (n-m<0 || n<0 || m<0) return 0;
	return frac[n]*revf[m]%oo*revf[n-m]%oo;
}

LL dp(int s, int x)
{
	if (s==0 && x!=k) return f[s][x]=0;
	if (f[s][x]!=-1) return f[s][x];
	f[s][x]=0;
	for (int i=0;i<=k-x;i++)
		if (n-sum[s-1]-(x+i)*2>=0)
		{
			LL tmp=dp(s-1,x+i)*Com(x+i, i)%oo;
			for (int j=0;j<=i;j++) 
				if (i*2-j<=c[s])
				{
					LL cnt=tmp*Com(i, j)%oo*Com(n-sum[s-1]-(x+i)*2, c[s]-(i*2-j))%oo;
					f[s][x]=(f[s][x]+cnt)%oo;
				}
		}
	return f[s][x];
}

int main()
{
	int Case;
	scanf("%d",&Case);
	frac[0]=revf[0]=1;
	for (int i=1;i<=100000;i++)
	{
		frac[i]=frac[i-1]*i%oo;
		revf[i]=exp(frac[i], oo-2, oo);
	}
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&k);
		sum[0]=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&c[i]);
			sum[i]=sum[i-1]+c[i];
		}
		memset(f,-1,sizeof(f));
		f[0][k]=1;
		LL ans=dp(m, 0);
		printf("Case #%d: %lld\n",o, ans);
	}
	return 0;
}