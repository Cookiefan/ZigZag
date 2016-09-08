#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 5
using namespace std;
typedef long long llg;
llg n,a,b,c,p,q;

struct matrix
{
	llg e[maxn][maxn];
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	matrix()
	{
		clear();
	}
	matrix(int x)
	{
		clear();
		for (int i=0;i<4;i++) e[i][i]=x;
	}
	
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int k=0;k<4;k++)
			for (int i=0;i<4;i++)
				for (int j=0;j<4;j++)
					(c.e[i][j]+=a.e[i][k]*b.e[k][j]%q)%=q;
		return c;
	}
	friend matrix operator ^(matrix e, llg k)
	{
		matrix tmp=matrix(1);
		while (k)
		{
			if (k&1) tmp=tmp*e;
			k=k>>1;
			e=e*e;
		}
		return tmp;
	}
};

llg power(llg e, llg k)
{
	llg tmp=1;
	e=e%p;
	while (k)
	{
		if (k&1) tmp=(tmp*e)%p;
		k=k>>1;
		e=(e*e)%p;
	}
	return tmp;
}


int main()
{
	matrix T, X;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%I64d%I64d%I64d%I64d%I64d",&n,&a,&b,&c,&p);
		q=(p-1);
		T.clear();
		T.e[0][0]=c; T.e[0][1]=1;
		T.e[1][0]=1; T.e[1][2]=1;
		T.e[3][0]=1; T.e[3][3]=1;
		X.clear();
		X.e[0][0]=1;
		X.e[0][1]=0;
		X.e[0][2]=0;
		X.e[0][3]=1;
		
		T=T^n;
		X=X*T;
		//for (int i=0;i<4;i++) cout<<X.e[0][i]<<' '; cout<<endl;
		llg d=power(a,b);
		printf("%I64d\n",power(d,X.e[0][2]));
	}
	return 0;
}