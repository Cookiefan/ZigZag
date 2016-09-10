#include <bits/stdc++.h>
#define maxn 120000

using namespace std;
typedef long long LL;
const LL oo=1e9+7;
LL f[maxn], s[maxn];
map<int, LL> g;

LL inv(LL x)
{
	if (x==1) return 1;
	else return (oo-oo/x)*inv(oo%x)%oo;
}

const int ms=4;
struct matrix
{
	LL e[ms][ms];
	matrix()
	{
		memset(e,0,sizeof(e));
	}
	matrix(int x)
	{
		memset(e,0,sizeof(e));
		for (int i=0;i<ms;i++) e[i][i]=x;
	}
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int k=0;k<ms;k++)
			for (int i=0;i<ms;i++)
				for (int j=0;j<ms;j++)
					(c.e[i][j]+=a.e[i][k]*b.e[k][j]%oo)%=oo;
		return c;
	}
	friend matrix operator ^(matrix e, LL k)
	{
		matrix tmp=matrix(1);
		while (k)
		{
			if (k&1) tmp=tmp*e;
			k=k>>1;
			e=e*e;
		}
		return tmp;
	};
};

int fibo(int x)
{
	if (x==1) return 1;
	matrix S, T;
	S.e[0][0]=3; S.e[0][1]=4;
	T.e[0][0]=0; T.e[0][1]=1;
	T.e[1][0]=1; T.e[1][1]=1;
	if (x>2)
	{
		T=T^(x-2);
		S=S*T;
	}
	return S.e[0][0];
}

int dp(int x)
{
	if (g.count(x)) return g[x];
	LL tmp=(fibo(x)-1+x)%oo;
	//cout<<0<<' '<<fibo(x)<<endl;
	for (int i=2;i*i<=x;i++)
		if (x%i==0)
		{
			(tmp+=(fibo(i)-1+oo)%oo)%=oo;
			if (x/i!=i)
				(tmp+=(fibo(x/i)-1+oo)%oo)%=oo;
		}
	tmp=tmp*inv(x)%oo;
	return g[x]=tmp;
}

LL gcd(LL a,LL b)
{
    return (b==0?a:gcd(b, a%b));
}


int main()
{
	for (int i=1;i<=20;i++) 
	{
		int tmp=0;
		for (int j=1;j<=i;j++)
			tmp+=fibo(gcd(i, j));
		tmp=tmp/i;
		cout<<i<<' '<<tmp<<endl;
	}
	g[1]=2;
	//for (int i=1;i<=100000;i++) dp(i);
	int n;
	while (scanf("%d",&n)!=EOF)
	{
		printf("%d\n",dp(n));
	}
	return 0;
}