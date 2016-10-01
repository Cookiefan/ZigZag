//NTT
#define G 3
//mod[0]=998244353;
//mod[1]=1004535809;
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

inline void roll(LL *a, LL *b, LL *c, int n, int m)
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
merge
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
//求原根(MOD=P * 2^k + 1)
int g = 2;
while (exp(g, (MOD - 1) / 2, MOD) == 1 || exp(g, (MOD - 1) / 479, MOD) == 1) {
    g ++;
}
//当中间结果可能超过10^16时，FFT精度会GG
//所以要用NTT对两个10^9级别的数取模
//再对两个结果用CRT合并一下
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