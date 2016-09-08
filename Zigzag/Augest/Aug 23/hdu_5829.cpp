#include <bits/stdc++.h>
#define maxn 420000
using namespace std;
#define G 3
typedef long long LL;
const LL mod=998244353;
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
	for (int i=1;i<n;i<<=1)
	{
		tmp<<=1;
		if (x & i) tmp |=1;
	}
	return tmp;
}
inline void ntt(LL *a, int n, int flag)
{
	for (int i=0;i<n;i++)
		if (i<rev(i, n))
			swap(a[rev(i, n)], a[i]);
	for (int i=1;i<n;i<<=1)
	{	
		LL wn=exp(G, (mod-1)/(i<<1), mod);
		if (flag==-1) wn=exp(wn, mod-2, mod);
		for (int j=0;j<n;j+=(i<<1))
		{
			LL w=1;
			for (int k=0;k<i;k++, w=w*wn%mod)
			{
				LL x=a[j+k], y=w*a[j+k+i]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+i]=(x-y+mod)%mod;
			}
		}
	}
	if (flag==-1)
	{
		LL inv=exp(n, mod-2, mod);
		for (int i=0;i<n;i++) a[i]=a[i]*inv%mod;
	}
}

inline void convolution(LL *a, LL *b, LL *c, int n, int m)
{
	int num=1;
	while (num<n+m) num<<=1;
	for (int i=0;i<num;i++) a[i]=(i<n)?a[i]:0;
	for (int i=0;i<num;i++) b[i]=(i<m)?b[i]:0;	
	ntt(a, num, 1);
	ntt(b, num, 1);
	for (int i=0;i<num;i++) c[i]=a[i]*b[i]%mod;
	ntt(c, num, -1);
}

LL p[maxn],step[maxn],pt[maxn],in_pt[maxn], in_step[maxn];
LL a[maxn],b[maxn],c[maxn],ans[maxn];
int n;


int main()
{
	step[0]=in_step[0]=pt[0]=in_pt[0]=1;
	for (int i=1;i<=100000;i++)
	{
		step[i]=step[i-1]*i%mod;
		in_step[i]=exp(step[i], mod-2, mod);
		pt[i]=pt[i-1]*2%mod;
		in_pt[i]=exp(pt[i], mod-2, mod);
	}
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%I64d",&p[i]);
		sort(p+1, p+n+1, greater<LL>());
		for (int i=0;i<n;i++)
		{
			a[i]=pt[n-i]*in_step[i]%mod;
			b[i]=step[n-i-1]*p[n-i]%mod;
		}
		convolution(a, b, c, n, n);
		for (int i=1;i<=n;i++)
		{
			ans[i]=c[n-i]*in_pt[i]%mod*in_step[i-1]%mod;
			ans[i]=(ans[i]+ans[i-1])%mod;
		}
		for (int i=1;i<=n;i++)
			printf("%I64d ",ans[i]);
		printf("\n");	
	}
	return 0;
}
