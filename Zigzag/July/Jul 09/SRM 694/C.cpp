#include <bits/stdc++.h>
#define maxn 120
#define oo 1000000007
using namespace std;

class UpDownNess
{
public:
	long long f[maxn][8000];
	UpDownNess(){memset(f,-1,sizeof(f));}
	long long dp(int n, int k)
	{
		if (f[n][k]!=-1) return f[n][k];
		if (n==1) return f[n][k]=(k==0);
		//if (n==2 && k>=1) return f[n][k]=0;
		//if (n==2 && k==0) return f[n][k]=2;
		long long tmp=0;
		for (int i=1;i<=n;i++)
			if (k-(i-1)*(n-i)>=0)
				tmp=(tmp+dp(n-1, k-(i-1)*(n-i)))%oo;
				//tmp=(tmp+dp(n-1, k-i*(n-1-i)))%=oo;
		return f[n][k]=tmp;
	}
	int count(int N, int K)
	{
		return dp(N,K);
	}
}t;

int main()
{
	int n,k;
	while (scanf("%d%d",&n,&k)!=EOF)
		cout<<t.count(n,k)<<endl;
	return 0;
}

