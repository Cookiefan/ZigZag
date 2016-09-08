#include <bits/stdc++.h>
#define maxn 100200
using namespace std;
int prime[maxn], np[maxn], mu[maxn];
int tot;
typedef long long LL;

vector<int> fact;
LL f[maxn];
int a[maxn];
int n,m;

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

int Mu(int x)
{
	if (x<=100000) return mu[x];
	int ans=1;
	for (int i=1;i<=tot;i++)
	{
		if (prime[i]>x) break;
		if (x%prime[i]==0)
		{
			if ((x/prime[i])%prime[i]!=0) ans*=-1;
			else ans=0;
		}
		while (x%prime[i]==0) x/=prime[i];
	}
	if (x!=1)
		ans*=-1;
	return ans;
}

int gcd(int a,int b)
{
    return (b==0?a:gcd(b, a%b));
}

int main()
{
	int Case;
	scanf("%d",&Case);
	get_prime(100000);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=0;i<=n;i++) fact.clear();
		for (int x=1;x*x<=m;x++)
			if (m%x==0)
			{
				fact.push_back(x);
				if (m/x!=x)
				fact.push_back(m/x);
			}
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(fact.begin(), fact.end());
		for (int i=fact.size()-1;i>=0;i--)
		{
			int flag=0;
			for (int j=1;j<=n;j++)
				if (fact[i]%gcd(a[j], m)==0)
					flag=1;
			if (!flag) fact[i]=-1;
		}
		memset(f,0,sizeof(f));
		LL ans=0;
		for (int i=fact.size()-1;i>=0;i--)
			if (fact[i]!=-1)
			{
				LL cnt=m/fact[i];
				f[i]=(LL)fact[i]*cnt*(cnt+1)/2;
				cout<<fact[i]<<' '<<f[i]<<' '<<Mu(fact[i])<<endl;
				ans+=f[i]*Mu(fact[i]);
			}
		printf("Case #%d: %I64d\n",o, ans+m);
	}
	return 0;
}