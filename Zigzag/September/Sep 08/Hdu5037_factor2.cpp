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

int gcd(int a,int b)
{
    return (b==0?a:gcd(b, a%b));
}

long long phi(long long x)
{
	long long cnt=x;
	for (long long i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x>1) cnt=cnt/x*(x-1);
	return cnt;
}

int main()
{
	int Case;
	scanf("%d",&Case);
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
			if (fact[i]!=m && fact[i]!=-1)
			{
				ans+=(LL)m*phi(m/fact[i])/2;;
			}
		printf("Case #%d: %I64d\n",o, ans);
	}
	return 0;
}