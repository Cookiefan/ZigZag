#include <bits/stdc++.h>
#define maxn 33000
#define low 20
using namespace std;
typedef long long LL;
typedef double LD;
const int oo=1e6+3;
const LD PI=acos(-1.0);
struct cpx
{
    LD x, y;
    cpx(LD _x=0, LD _y=0):x(_x), y(_y){}
    cpx operator +(const cpx &b)const{
    return cpx(x+b.x, y+b.y);
    }
    cpx operator -(const cpx &b)const{
        return cpx(x-b.x, y-b.y);
    }
    cpx operator *(const cpx &b)const{
        return cpx(x*b.x-y*b.y, x*b.y+y*b.x);
    }
};

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
LL f[25][maxn], g[maxn];
cpx A1[maxn<<1], B1[maxn<<1], A2[maxn<<1], B2[maxn<<1], A3[maxn<<1];
void roll(LL *a, LL *b, LL *c, int n, int m)
{
    int num=1;;
    int O=sqrt(oo);
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
    // freopen("H.in","r",stdin);
    scanf("%d%d%d",&n,&m,&p);
    for (int i='A';i<='Z';i++) f[0][i%m]+=1;
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
        LL tmp=1LL*g[i]*(g[i]-1)/2;
        ans=(ans+tmp)%oo;
    }
    printf("%d\n",ans);
    return 0;
}
