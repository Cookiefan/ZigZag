#include <bits/stdc++.h>
#define maxn 120000

using namespace std;
typedef long long LL;
const LL oo=1e9+7;
LL f[maxn], s[maxn];
map<int, LL> g;

LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

LL inv(LL x)
{
	return exp(x, oo-2, oo);
}

const int ms=2;
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
	matrix S, T;
	S.e[0][0]=1; S.e[0][1]=3;
	T.e[0][0]=0; T.e[0][1]=1;
	T.e[1][0]=1; T.e[1][1]=1;
	if (x>1)
	{
		T=T^(x-1);
		S=S*T;
	}
	return S.e[0][0];
}

int phi(int x)
{
	LL cnt=x;
	for (int i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt*inv(i)%oo*(i-1)%oo;
			while (x%i==0) x=(LL)x*inv(i)%oo;
		}
	if (x>1) cnt=cnt*inv(x)%oo*(x-1)%oo;
	return cnt;
}


int main()
{
	// for (int i=1;i<=2000;i++) 
	// {
	// 	int tmp=0;
	// 	for (int j=1;j<=i;j++)
	// 		(tmp+=fibo(gcd(i, j)))%=oo;
	// 	tmp=tmp*inv(i)%oo;
	// 	cout<<i<<' '<<tmp<<endl;
	// }
	int n;
	while (scanf("%d",&n)!=EOF)
	{
		int i=n;
		LL tmp=0;
		for (int j=1;j*j<=i;j++)
			if (i%j==0)
			{
				(tmp+=(LL)fibo(j)*phi(i/j)%oo)%=oo;
				if (i/j!=j) (tmp+=(LL)fibo(i/j)*phi(j)%oo)%=oo;
			}
		tmp=tmp*inv(i)%oo;
		if (n==1) tmp=2;
		cout<<tmp<<endl;
	}
	return 0;
}