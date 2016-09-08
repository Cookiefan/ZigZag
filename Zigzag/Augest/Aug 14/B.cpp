#include <bits/stdc++.h>
#define maxn 5000
using namespace std;

typedef long long LL;
vector<int> prime;
int np[maxn];
int num;
LL sum, ans, mx;

void get_prime(int n)
{
	memset(np,0,sizeof(np));
	for (int i=2;i<=n;i++)
	{
		if (!np[i])
		{
			prime.push_back(i);
		}
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)
				break;
		}
	}
}

void dfs(int k)
{
	if (k>=num)
	{
		//cout<<sum<<endl;
		ans++;
		return ;
	}
	dfs(k+1);
	if (sum<=(mx/prime[k]+1))
	{
		sum=sum*prime[k];
		dfs(k+1);
		sum=sum/prime[k];
	}
}


int main()
{
	get_prime(2000);
	num=prime.size();
	cout<<num<<endl;
	sum=1;
	ans=0;
	mx=1e18;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}