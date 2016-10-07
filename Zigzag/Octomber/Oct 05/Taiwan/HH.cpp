#include <bits/stdc++.h>
#define maxn 63000
#define low 20
#define G 3
using namespace std;
typedef long long LL;
const LL oo=1e6+3;
const LL mm[2]={998244353,1004535809};
LL mod;
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

int rev(int x, int n){
    int tmp=0;
    for (int i=n>>1;i;i>>=1, x>>=1)
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
                a[j]=x+y;
                while (a[j]>=mod) a[j]-=mod;
                a[j|k]=x-y+mod;
                while (a[j|k]>=mod) a[j|k]-=mod;
            }
    }
    if (flag==-1)
    {
        LL inv=exp(n, mod-2, mod);
        for (int i=0;i<n;i++) a[i]=a[i]*inv%mod;
    }
}

int n,m,p;
LL f[25][maxn], g[maxn], b[maxn];
LL A[maxn<<1], B[maxn<<1], C[3][maxn<<1];
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
    LL tmp=x*y-((LL)((double)x*y/p+1e-6 )*p);
    return tmp<0?tmp+p:tmp;
}

LL crt(int n, LL* a, const LL* p)
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

void roll(LL *a, LL *b, LL *c, int n, int m)
{
    int num=1;
    while (num<n+m) num<<=1;
    for (int k=0;k<2;k++)
    {
        mod=mm[k];
        for (int i=0;i<num;i++) A[i]=(i<n)?a[i]:0;
        for (int i=0;i<num;i++) B[i]=(i<m)?b[i]:0;  
        ntt(A, num, 1);
        ntt(B, num, 1);
        for (int i=0;i<num;i++) C[k][i]=A[i]*B[i]%mod;
        ntt(C[k], num, -1);    
    }
    LL tmp[2];
    for (int i=0;i<num;i++)
    {
        tmp[0]=C[0][i];
        tmp[1]=C[1][i];
        c[i]=crt(2, tmp, mm)%oo;
        if (i>=m)
        {
            c[i%m]=(c[i%m]+c[i])%oo;
            // while (c[i%m]>=oo) c[i%m]-=oo;
        }
    }       
}

int main()
{
    // freopen("H.in","r",stdin);
    scanf("%d%d%d",&n,&m,&p);
    //memset(f, 0, sizeof(f));
    for (int i='A';i<='Z';i++)
        f[0][i%m]++,
    //memset(g, 0, sizeof(g));
    g[0]=1;
    LL shift=p;
     for (int k=0;k<=low;k++)
    {
        if (n&1)
        {
            memset(b, 0, sizeof(b));
            for (int i=0;i<m;i++)
            {
                int j=(LL)i*shift%m;
                b[j]=b[j]+g[i];
                while (b[j]>=oo) b[j]-=oo;
            }
            roll(f[k], b, g, m, m);
        }
        memset(b, 0, sizeof(b));
        for (int i=0;i<m;i++)
        {
            int j=(LL)i*shift%m;
            b[j]=b[j]+f[k][i];
            while (b[j]>=oo) b[j]-=oo;
        }
        roll(f[k], b, f[k+1], m, m);
        n>>=1;
        if (!n) break;
        shift=shift*shift%m;
    }   
    //for (int i=0;i<m;i++) cout<<g[i]<<' '; cout<<endl;

    LL ans=0;
    for (int i=0;i<m;i++)
    {
        LL tmp=g[i]*(g[i]-1)/2%oo;
        ans=(ans+tmp)%oo;
    }
    printf("%d\n",ans);
    return 0;
}
