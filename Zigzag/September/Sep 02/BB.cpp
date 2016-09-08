#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
int f[maxn], g[maxn], h[maxn], p[maxn], phi[maxn];
int np[maxn];
vector<int> prime;
int n;

void get_prime(int n)
{
	memset(np,0,sizeof(np));
	phi[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!np[i])
		{
			prime.push_back(i);
			phi[i]=i-1;
		}
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}


int main()
{
	memset(p,0,sizeof(p));
	memset(phi,0,sizeof(phi));
	get_prime(100000);
	for (int o=1;o<=100000;o++)
	{
		for (int x=1;x<=o;x++)
			if (o%x==0)
				p[o]+=x*phi[o/x];
		//cout<<p[2016]<<endl;
		f[o]=o*o-p[o];
	}
	int Case;
	scanf("%d",&Case);
	// for (int o=1;o<=Case;o++)
	// {
	// 	scanf("%d",&n);
	// 	for (int i=1;i<=)
	// }
	return 0;
}