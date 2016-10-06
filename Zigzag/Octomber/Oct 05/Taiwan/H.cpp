#include <bits/stdc++.h>
#define maxn 33000
#define low 20
using namespace std;
typedef long long LL;
typedef double LD;
const LL oo=1e6+3;
const LD PI=acos(-1.0);
struct cpx
{
    LD x, y;
    cpx(LD _x=0, LD _y=0):x(_x), y(_y){}
};
cpx operator +(cpx a, cpx b){
    return cpx(a.x+b.x, a.y+b.y);
}
cpx operator -(cpx a, cpx b){
    return cpx(a.x-b.x, a.y-b.y);
}
cpx operator *(cpx a, cpx b){
    return cpx(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}
int rev(int x, int n){
    int tmp=0;
    for (int i=n>>1;i;i>>=1, x>>=1)
        tmp=tmp<<1|x&1;
    return tmp;
}
void fft(cpx *a, int n, int flag){
    for (int i=0,j=i;i<n;i++, j=rev(i,n))
        if (i<j) swap(a[i], a[j]);
    for (int k=1;k<n;k<<=1){
        cpx wn(cos(PI/k), flag*sin(PI/k));
        cpx w(1, 0);
        for (int i=0;i<k;i++,w=w*wn)
            for (int j=i;j<n;j+=(k<<1)){
                cpx x=a[j], y=w*a[j|k];
                a[j]=x+y;
                a[j|k]=x-y;
            }
    }
    if (flag==-1)
        for (int i=0;i<n;i++)
            a[i].x/=n;
}

LL b[maxn], c[maxn];
int n,m,p;
LL f[22][maxn], g[maxn];
cpx A1[maxn<<1], B1[maxn<<1], A2[maxn<<1], B2[maxn<<1], A3[maxn<<1];
void roll(LL *a, LL *b, LL *c, int n, int m)
{
    int num=1;;
    LL O=sqrt(oo);
    while (num<n+m) num<<=1;
    for (int i=0;i<num;i++)
    {
        A1[i]=(i<m?a[i]/O:0);
        A2[i]=(i<m?a[i]%O:0);
        A3[i]=0;
        B1[i]=(i<m?b[i]/O:0);
        B2[i]=(i<m?b[i]%O:0);
    }
    fft(A1,num,1);fft(A2,num,1);
    fft(B1,num,1);fft(B2,num,1);
    for (int i=0;i<num;i++)
    {
        A3[i]=A1[i]*B2[i]+A2[i]*B1[i];
        A1[i]=A1[i]*B1[i];
        A2[i]=A2[i]*B2[i];
    }
    fft(A1,num,-1);fft(A2,num,-1);fft(A3,num,-1);
    for (int i=0;i<num;i++)
    {
        LL x=(A1[i].x+0.5), y=(A2[i].x+0.5), z=(A3[i].x+0.5);
        c[i]=(x*O*O+y+z*O)%oo;
        if (i>=m)
        {
            c[i%m]=c[i%m]+c[i];
            while (c[i%m]>=oo) c[i%m]-=oo;
        }
    }
}

int main()
{
    freopen("H.in","r",stdin);
    scanf("%d%d%d",&n,&m,&p);
    memset(f, 0, sizeof(f));
    for (int i='A';i<='Z';i++)
        f[0][i%m]+=1;
    LL shift=p;
    for (int k=1;k<=low;k++,shift=shift*shift%m)
    {
        memset(b, 0, sizeof(b));
        for (int i=0;i<m;i++)
        {
            int j=i*shift%m;
            b[j]=b[j]+f[k-1][i];
            while (b[j]>=oo) b[j]-=oo;
        }
        roll(f[k-1], b, f[k], m, m);
    }
    memset(g, 0, sizeof(g));
    g[0]=1;
    shift=p;
    for (int k=0;k<=low;k++, shift=shift*shift%m)
        if ((n>>k)&1)
        {
            memset(b, 0, sizeof(b));
            for (int i=0;i<m;i++)
            {
                int j=i*shift%m;
                b[j]=b[j]+g[i];
                while (b[j]>=oo) b[j]-=oo;
            }
            roll(f[k], b, g, m, m);
        }
    LL ans=0;
    for (int i=0;i<m;i++)
    {
        LL tmp=g[i]*(g[i]-1)/2;
        tmp=(tmp%oo+oo)%oo;
        ans+=tmp;
        while (ans>=oo) ans-=oo;
    }
    printf("%d\n",ans);
    return 0;
}
