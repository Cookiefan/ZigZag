#include <bits/stdc++.h>
#define maxn 1500020
#define oo 2980001
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pll;
int prime[maxn], np[maxn], mu[maxn], f[maxn];
vector<pll> hx[3000000];
int tot;
//莫比乌斯反演
void get_prime(int n)
{
    memset(np,0,sizeof(np));
    tot=0;
    mu[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!np[i])
        {
            prime[++tot]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=tot && i*prime[j]<=n;j++)
        {
            np[i*prime[j]]=1;
            if (i%prime[j]) mu[i*prime[j]]=-mu[i];
            else
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
}

LL a, b;

inline LL dp(LL x)
{
    if (x<=1500000) return f[x];
    for (pll i:hx[x%oo]) if (i.first==x) return i.second;
    LL tmp=1;
    for (LL i=2, j;i<=x;i=j+1)
    {
        j=x/(x/i);
        tmp-=dp(x/i)*(j-i+1);
    }
    hx[x%oo].push_back(pll(x, tmp));
    return tmp;
}

int main()
{
    get_prime(1500000);
    f[1]=1;
    for (int i=2;i<=1500000;i++)
        f[i]=f[i-1]+mu[i];

    scanf("%I64d%I64d",&a, &b);
    printf("%I64d\n",dp(b)-dp(a-1));
    return 0;
}