#include <bits/stdc++.h>
#define maxn 1000200
using namespace std;
typedef long long LL;
int np[maxn], mu[maxn], prime[maxn];
int tot, cnt;
LL ans, now, coe;
LL sum;
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
vector<int> num;

void dfs(int k, LL now, int t)
{
	if (t==0)
	{
		sum+=n/now;
		return ;
	}
	LL tmp;
	for (int i=k;i<cnt-t+1;i++)
	{
		now=now*num[i];
		tmp=sum;
		if (now<=n) dfs(i+1, now, t-1);
		if (tmp==sum) return ;
		now=now/num[i];
	}
}


int main()
{	
	get_prime(400000);
	while (scanf("%I64d",&n)!=EOF)
	{
		num.clear();
		ans=0;
		int x=sqrt(n*1.0);
		for (int i=1;i<=tot;i++)
			if (prime[i]<=x)
				num.push_back(prime[i]);
		cnt=num.size();
		for (int i=1;i<=cnt;i++)
		{
			sum=0;
			dfs(0, 1, i);
			if (sum==0) break;
			if (i&1) ans+=sum;
			else ans-=sum;
		}
		ans-=cnt;
		ans=n-ans-1;
		printf("%I64d\n",ans);
	}
	return 0;
}