#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

int n,m;

int f[5000];

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		memset(f,0,sizeof(f));
		long long  ans=0;
		for (int i=2016;i>=1;i--)
			if (2016%i==0)
			{
				f[i]=n/i;
				for (int j=i+1;j<=2016;j++)
					if (2016%j==0 && j%i==0)
						f[i]-=f[j];
				ans+=(long long)f[i]*((long long)i*m/2016);
			}
		printf("%I64d\n",ans);
	}

	return 0;
}