#include <bits/stdc++.h>
#define maxn 400200
#define G 3
#define mk 17
#define mod 1004535809
using namespace std;
typedef long long LL;
LL f[maxn], g[maxn], fac[maxn], inv[maxn];
LL a[maxn], b[mk+1][maxn], c[maxn];
int n;
inline LL exp(LL a, LL b, LL p)
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
inline int rev(int x, int n)
{
    int tmp=0;
    for (int i=n>>1;i;i>>=1,x>>=1)
        tmp=tmp<<1|x&1;
    return tmp;
}
inline void ntt(LL *a, int n, int flag)
{
	for (int i=0,j=i;i<n;i++,j=rev(i, n))
		if (i<j) swap(a[i], a[j]);
	for (int k=1;k<n;k<<=1)
	{	
		LL wn=exp(G, (mod-1)/(k<<1), mod), w=1;
		if (flag==-1) wn=exp(wn, mod-2, mod);
		for (int i=0;i<k;i++,w=w*wn%mod)
			for (int j=i;j<n;j+=(k<<1))
			{
				LL x=a[j], y=w*a[j|k]%mod;
				a[j]=(x+y)%mod;
				a[j|k]=(x-y+mod)%mod;
			}
	}
	if (flag==-1)
	{
		LL inv=exp(n, mod-2, mod);
		for (int i=0;i<n;i++) a[i]=a[i]*inv%mod;
	}
}
inline void solve(int l, int k)
{
	if (k==0)
	{
		f[l]=f[l]*exp(l, mod-2, mod)%mod;
		return ;
	}
	int r=l+(1<<k)-1, mid=(l+r)>>1;
	solve(l, k-1);
	memset(a, 0, sizeof(*a)<<k);
	//cout<<k<<endl;
	for (int i=l;i<=mid;i++) a[i-l]=f[i];
	ntt(a, 1<<k, 1);
	for (int i=0;i<1<<k;i++) (a[i]*=b[k][i])%=mod;
	ntt(a, 1<<k, -1);
	for (int i=mid+1;i<=r;i++)
		(f[i]+=a[i-l-1])%=mod;
	solve(mid+1, k-1);
}


int main()
{
	fac[0]=1;
	for (int i=1;i<=200000;i++) fac[i]=fac[i-1]*i%mod;
	inv[200000]=exp(fac[200000], mod-2, mod);
	for (int i=199999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	g[1]=1;
	for (int i=2;i<=200000;i++) g[i]=exp(i, i-2, mod)*inv[i-1]%mod;
	for (int i=1;i<=200000;i++) f[i]=g[i];
	for (int k=1;k<=mk;k++)
	{
		for (int i=0;i<1<<k;i++)
			b[k][i]=g[i+1];
		ntt(b[k], 1<<k, 1);
	}
	solve(0, mk);

	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		LL sum=exp(2, (LL)n*(n-1)/2, mod);
		LL tmp=f[n]*fac[n]%mod;
		printf("%d\n",(sum-tmp+mod)%mod);
	}
	return 0;
}
