#include <bits/stdc++.h>
#define maxn 52000
#define maxm 220
using namespace std;

int np[maxn];
int f[maxn], mu[maxn];
int sum[maxn][maxm], ans[maxn];
int a[maxn];
int n, tot, m, p;

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

int main()
{
	get_prime(maxm);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		m=(int)sqrt(n)+5;
		
		scanf("%d",&p);
		int l, r;
		for (int i=1;i<=p;i++)
		{
			scanf("%d%d",&l,&r);
			

		}


	}

	return 0;
}