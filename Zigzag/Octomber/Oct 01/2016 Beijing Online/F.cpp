#include <bits/stdc++.h>
#define maxn 420060
#define G 3
using namespace std;
typedef long long LL;
LL a[maxn], b[maxn], c[maxn], d[maxn], e[3], mod[3], A[maxn], B[maxn];
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
inline void ntt(LL *a, int n, int flag, int z)
{
	for (int i=0,j=i;i<n;i++,j=rev(i, n))
		if (i<j) swap(a[i], a[j]);
	for (int k=1;k<n;k<<=1)
	{	
		LL wn=exp(G, (mod[z]-1)/(k<<1), mod[z]), w=1;
		if (flag==-1) wn=exp(wn, mod[z]-2, mod[z]);
		for (int i=0;i<k;i++,w=w*wn%mod[z])
			for (int j=i;j<n;j+=(k<<1))
			{
				LL x=a[j], y=w*a[j|k]%mod[z];
				a[j]=(x+y)%mod[z];
				a[j|k]=(x-y+mod[z])%mod[z];
			}
	}
	if (flag==-1)
	{
		LL inv=exp(n, mod[z]-2, mod[z]);
		for (int i=0;i<n;i++) a[i]=a[i]*inv%mod[z];
	}
}

inline void roll(LL *a, LL *b, LL *c, int n, int m, int z)
{
	int num=1;
	while (num<m) num<<=1;
	for (int i=0;i<num;i++) A[i]=(i<n)?a[i]:0;
	for (int i=0;i<num;i++) B[i]=(i<m)?b[i]:0;	
	ntt(A, num, 1, z);
	ntt(B, num, 1, z);
	for (int i=0;i<num;i++) c[i]=A[i]*B[i]%mod[z];
	ntt(c, num, -1, z);
}

LL ex_gcd(LL a, LL b, LL &x, LL &y)
{
    if (!b){
        x=1, y=0;
        return a;
    }
    else{
        LL d=ex_gcd(b, a % b, y, x);
        y-=a/b*x;
        return d;
    }
}

LL mul( LL x, LL y, LL p )
{
    LL tmp=((LL)((double)x*y/p+1e-6 )*p);
    return x*y - tmp;
}


LL crt(int n, LL* a, LL* p)
{
    LL pp=1, tmp=0;
    for(int i=0;i<n;i++) pp=pp*p[i];
    for(int i=0;i<n;i++)
    {
        LL m=pp/p[i], x, y;
        ex_gcd(m,p[i],x,y);
        x=(x%p[i]+p[i])%p[i];
        tmp=(tmp+mul(mul(a[i],m,pp),x,pp))%pp;//注意overflow
    }
    return tmp;
}

LL gcd(LL a,LL b)
{
    return (b==0?a:gcd(b, a%b));
}


int main()
{
	mod[0]=998244353;
	mod[1]=1004535809;
	//freopen("FF.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for (int i=0;i<n;i++) scanf("%lld",&a[i]);
		for (int i=0;i<n;i++) scanf("%lld",&b[i]);
		LL ans=0;
		for (int i=0;i<n;i++) ans+=a[i]*a[i]+b[i]*b[i];
		reverse(b,b+n);
		for (int i=n;i<2*n;i++) b[i]=b[i-n];
		roll(a, b, c, n, 2*n, 0);
		roll(a, b, d, n, 2*n, 1);
		LL tmp=0;
		for (int i=n;i<2*n;i++)
		{
			e[0]=c[i];
			e[1]=d[i];
			tmp=max(tmp, crt(2, e, mod)*2);
		}

		printf("%lld\n", ans-tmp);
	}
	return 0;
}