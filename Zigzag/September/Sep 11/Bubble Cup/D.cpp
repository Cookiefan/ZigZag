#include <bits/stdc++.h>
#define maxn 1200
using namespace std;

//矩阵乘法&快速幂
const int ms=130;
struct matrix
{
	double e[ms][ms];
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
					c.e[i][j]+=a.e[i][k]*b.e[k][j];
		return c;
	}
	friend matrix operator ^(matrix e, int k)
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

int n,m;
double p[maxn];

int main()
{
	scanf("%d%d",&n,&m);
	memset(p,0,sizeof(p));
	for (int i=0;i<=m;i++) scanf("%lf",&p[i]);
	matrix S, T;
	for (int i=0;i<128;i++)
		for (int j=0;j<128;j++)
			T.e[i][i^j]+=p[j];
	S.e[0][0]=1;
	T=T^n;
	S=S*T;
	printf("%.6f\n",1-S.e[0][0]);
	return 0;
}