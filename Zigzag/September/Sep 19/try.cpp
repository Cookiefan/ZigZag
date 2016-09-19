#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
#define maxn 222222
#define mod 313
#define PI acos(-1.0) 
struct complex
{
    double r,i;
    complex(double _r=0,double _i=0)
    {
        r=_r,i=_i;
    }
    complex operator +(const complex &b)
    {
        return complex(r+b.r,i+b.i);
    }
    complex operator -(const complex &b)
    {
        return complex(r-b.r,i-b.i);
    }
    complex operator *(const complex &b)
    {
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
void change(complex *x,int len)
{
    for(int i=1,j=len/2;i<len-1;i++)
    {
        if(i<j)swap(x[i],x[j]);
        int k=len/2;
        while(j>=k)
        {
            j-=k;
            k/=2;
        }
        if(j<k)j+=k;
    }
}
void fft(complex *x,int len,int sta)
{
    change(x,len);
    for(int m=2;m<=len;m<<=1)
    {
        complex Wn(cos(-sta*2*PI/m),sin(-sta*2*PI/m));
        for(int i=0;i<len;i+=m)
        {
            complex W(1,0);
            for(int j=i;j<i+m/2;j++)
            {
                complex x1=x[j],x2=W*x[j+m/2];
                x[j]=x1+x2,x[j+m/2]=x1-x2;
                W=W*Wn;
            }
        }
    }
    if(sta==-1)
        for(int i=0;i<len;i++)
            x[i].r/=len;
}
int n,a[2*maxn],b[2*maxn],dp[maxn];
complex x[2*maxn],y[2*maxn];
void deal(int l,int r)
{
    if(l==r)
    {
        dp[l]+=a[l],dp[l]%=mod;
        return ; 
    }
    int mid=(l+r)>>1;
    deal(l,mid);
    int len=1;
    while(len<=r-l+1)len<<=1;
    for(int i=0;i<len;i++)
    {
        if(i+l<=mid)x[i]=complex(dp[i+l],0);
        else x[i]=complex(0,0);
        if(l+i+1<=r)y[i]=complex(a[i+1],0);
        else y[i]=complex(0,0);
    }
    fft(x,len,1),fft(y,len,1);
    for(int i=0;i<len;i++)x[i]=x[i]*y[i];
    fft(x,len,-1);
    for(int i=0;i<len;i++)b[i]=(ll)(x[i].r+0.5)%mod;
    for(int i=mid+1;i<=r;i++)
        dp[i]+=b[i-l-1],dp[i]%=mod;
    deal(mid+1,r);
}
int main()
{
    while(scanf("%d",&n),n)
    {
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]%=mod;
        deal(1,n);
        printf("%d\n",dp[n]);
    }
    return 0;
}