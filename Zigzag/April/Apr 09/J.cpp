#include <bits/stdc++.h>
#define maxn 2020
#define oo 1000000007
using namespace std;

typedef long long LL;
LL f[maxn][maxn], g[maxn][maxn];
int p[maxn];
int n;


struct bitree
{
	LL b[2*maxn];
	int num;
	bitree(){}
	bitree(int n):num(n){}
	void add(int x, LL z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]=(b[i]+z)%oo;
	}
	LL ask(int x)
	{
		LL tmp=0;
		for (int i=x;i>0;i-=(i&-i)) tmp=(tmp+b[i])%oo;
		return tmp;
	}
	void init()
	{
		memset(b,0,sizeof(b));
	}
};

int main()
{
	//freopen("j.in","r",stdin);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&p[i]);
	for (int i=1;i<=n;i++)
	{
		g[i][1]=1;
		for (int j=2;j<=i;j++)
			g[i][j]=(g[i-1][j-1]+g[i-1][j])%oo*j%oo;
	}

	// for (int i=1;i<=n;i++)
	// {
	// 	for (int j=1;j<=n;j++)
	// 		cout<<g[i][j]<<' ';
	// 	cout<<endl;
	// }
	
	bitree s=bitree(n+1);
	s.init();
	LL ans=0;
	for (int i=1;i<=n;i++)
	{
		f[1][i]=1;
		//s.add(p[i],f[1][i]);
		ans=(ans+f[1][i]*g[n][1]%oo)%oo;
	}
	
	for (int i=2;i<=n;i++)
	{
		for (int j=i;j<=n;j++)
		{
			s.add(p[j-1],f[i-1][j-1]);
			f[i][j]=s.ask(p[j]-1);
			ans=(ans+f[i][j]*g[n][i]%oo)%oo;
		}
		s.init();
		// for (int j=i;j<=n;j++)
		// 	s.add(p[j], f[i][j]);
	}
	printf("%I64d\n",ans);
	return 0;
}