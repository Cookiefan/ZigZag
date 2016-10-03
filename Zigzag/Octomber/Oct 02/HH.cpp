#include <bits/stdc++.h>
#define maxn 2002000
#define oo 1000000007
using namespace std;

typedef long long LL;

LL fac[maxn], invf[maxn];
LL s[maxn], f[maxn];

struct edge
{
    int t;
    LL val;
    edge(){}
    edge(int t, LL val):
    t(t),val(val){}
};
vector<edge> e[maxn];
int n;
LL sum;

LL exp(LL a, LL b, LL p)
{
    a%=p;
    LL tmp=1;
    while (b){
        if (b&1) tmp=tmp*a%p;
        a=a*a%p;
        b>>=1;
    }
    return tmp;
}

LL com(int n, int m, LL p)
{
    LL tmp=fac[n]*invf[m]%p*invf[n-m]%p;
    return tmp;
}

void dfs(int x, int fa)
{
    f[x]=1;
    for (int j=0;j<e[x].size();j++)
    {
        int y=e[x][j].t;
        if (y==fa) continue;
        dfs(y, x);
        f[x]=f[x]*com(s[y]+e[x][j].val-1, s[y], oo)%oo*f[y]%oo;
        s[x]=s[x]+e[x][j].val;
    }
    f[x]=f[x]*fac[s[x]]%oo;
}

LL cnt(int x, LL p)
{
    LL tmp=1;
    for (int i=2;i<=2*x;i+=2)
        tmp=tmp*com(2*x-i+2, 2, oo)%oo;
    tmp=tmp*invf[x]%oo;
    return tmp;
}

int main()
{
    //freopen("H.in","r",stdin);
    int mx=2000000;
    fac[0]=1;
    for (int i=1;i<=mx;i++) fac[i]=fac[i-1]*i%oo;
    invf[mx]=exp(fac[mx], oo-2, oo);
    for (int i=mx-1;i>=0;i--) invf[i]=invf[i+1]*(i+1)%oo;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) e[i].clear();
    int x, y, z;
    sum=1;
    for (int i=1;i<n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        sum=sum*cnt(z, oo)%oo*exp(2, z, oo)%oo;
        e[x].push_back(edge(y, z));
        e[y].push_back(edge(x, z));
    }
    memset(s,0,sizeof(s));
    dfs(1, 0);
    LL ans=f[1]*sum%oo;
    printf("%lld\n",ans);

    return 0;
}