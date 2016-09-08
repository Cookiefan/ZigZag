//KD-Tree
//维护K维空间上离某点最近的点序
//HDU4347
#include <bits/stdc++.h>
#define maxn 1002000 
using namespace std;

vector<int> prime;
int np[maxn];

void get_prime(int n)
{
	memset(np,0,sizeof(np));
	prime.clear();
	for (int i=2;i<=n;i++)
	{
		if (!np[i]) prime.push_back(i);
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)break;
		}
	}
}
int n,num;

int main()

	get_prime(1000000);
	num=prime.size();
	int o=0;
	char sign;
	int x;
	while (scanf("%d",&n)&&n)
	{
		scanf(" %c%d",&sign,&x);
		if (sign=='I')
		{

		}
		else if (sign=='D')
		{

		}
		else
		{

		}


	}
	return 0;
}