#include <bits/stdc++.h>
#define maxn 1000200
using namespace std;
typedef long long LL;
int np[maxn], mu[maxn], prime[maxn];
int tot;
LL ans, now, coe;
int sum;
LL n;
void get_prime(int n)
{
    memset(np,0,sizeof(np));
    tot=0;
    mu[1]=1;
    np[1]=1;
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

void dfs(int k)
{
	if (k<1)
	{
		if (now==1) return ;
		ans+=coe*(n/now-(sum==1));
		return ;
	}
	dfs(k-1);
	now*=prime[k];
	coe*=(-1);
	sum++;
	if (now<=n) dfs(k-1);
	now/=prime[k];
	coe*=(-1);
	sum--;
}

int main()
{	
	get_prime(400000);
	while (scanf("%I64d",&n)!=EOF)
	{
		ans=0, now=1, coe=-1, sum=0;
		dfs(tot);
		printf("%I64d\n",n-ans-1);
	}
	return 0;
}