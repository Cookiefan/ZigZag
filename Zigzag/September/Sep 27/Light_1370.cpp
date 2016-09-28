#include <bits/stdc++.h>
#define maxn 2002000
using namespace std;

int np[maxn];
vector<int> prime;
typedef long long LL;
int a[maxn];
int n;

void get_prime(int num)
{
	prime.clear();
	memset(np,0,sizeof(np));
	for (int i=2;i<=num;i++)
	{
		if (!np[i]) prime.push_back(i);
		for (int j=0;j<prime.size() && i*prime[j]<=num;j++)
		{
			np[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}

int main()
{
	get_prime(2000000);
	//for (int i=0;i<prime.size();i++) cout<<prime[i]<<endl;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=0;i<n;i++) scanf("%d",&a[i]);
		sort(a, a+n);
		int j=0;
		LL ans=0;
		for (int i=0;i<n;i++)
		{
			while (a[i]>prime[j]-1) j++;
			ans+=prime[j];
		}
		printf("Case %d: %lld Xukha\n",o,ans);
	}
	return 0;
}