#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pll;

LL frac[220000];
const LL oo=110119;

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

LL com(LL n,LL m,LL p)
{
	if (m>n) return 0;
	LL ans=frac[n]*exp(frac[m], p-2, p)%p*exp(frac[n-m], p-2, p)%p;
	return ans;
}

LL lucas(LL n,LL m,LL p)
{
	if (m==0) return 1;
	return com(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}

LL get_ans(LL dx, LL dy)
{
	if (!(dx>=0 && dy>=0 && dx*2>=dy && (dx*2-dy)%3==0 && (dy*2>=dx && (dy*2-dx)%3==0)))
		return 0;
	LL x=(dx*2-dy)/3;
	LL y=(dy*2-dx)/3;
	return lucas(x+y, y, oo);
}

LL f[maxn];
vector<pll> q;
int p;
LL n,m,ans,tmp,x,y;

int main()
{
	int o=0;
	frac[0]=1;
	for (int i=1;i<=150000;i++) frac[i]=frac[i-1]*i%oo;
	while (scanf("%I64d%I64d%d",&n,&m,&p)!=EOF)
	{
		memset(f,0,sizeof(f));
		for (int i=1;i<=p;i++) scanf("%I64d%I64d",&x[i],&y[i]);
		x[0]=y[0]=1;
		x[p+1]=n; y[p+1]=m;

		f[0]=1;
		ans=tmp=0;
		for (int i=1;i<=p;i++)
		{
			f[i]=get_ans(x[i]-x[0], y[i]-y[0]);
			// cout<<i<<' '<<f[i]<<endl;
			for (int j=1;j<=p;j++)
			{
				if (i==j) continue;
				f[i]=(f[i]-f[j]*get_ans(x[i]-x[j], y[i]-y[j])%oo+oo)%oo;
				//cout<<i<<' '<<j<<' '<<get_ans(x[j]-x[i], y[j]-y[i])<<endl;
			}
			tmp=(tmp+f[i]*get_ans(x[p+1]-x[i], y[p+1]-y[i])%oo)%oo;
		}
		ans=(get_ans(x[p+1]-x[0], y[p+1]-y[0])-tmp+oo)%oo;
		printf("Case #%d: %I64d\n",++o,ans);
	}


	return 0;
}