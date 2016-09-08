#include <bits/stdc++.h>
#define maxn 6
#define oo 1000000007
using namespace std;
typedef long long llg;

struct matrix
{
	llg e[maxn][maxn];
	matrix()
	{
		memset(e,0,sizeof(e));
	}
	matrix(int x)
	{
		memset(e,0,sizeof(e));
		for (int i=0;i<5;i++) e[i][i]=x;
	}
	friend matrix operator *(matrix &a, matrix &b)
	{
		matrix c;
		for (int k=0;k<5;k++)
			for (int i=0;i<5;i++)
				for (int j=0;j<5;j++)
					(c.e[i][j]+=a.e[i][k]*b.e[k][j]%oo)%=oo;
		return c;
	}
	friend matrix operator ^(matrix &e, llg k)
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
}S,T;
llg ax,ay,ao,bo,bx,by;
llg n;

int main()
{
	while (scanf("%I64d",&n)!=EOF)
	{
		scanf("%I64d%I64d%I64d%I64d%I64d%I64d",&ao,&ax,&ay,&bo,&bx,&by);
		if (n<=0)
		{
			printf("0\n");
			continue;
		}
		T=matrix(0);
		T.e[0][0]=ax; T.e[0][1]=0; T.e[0][2]=ax*by%oo; T.e[0][3]=ax*by%oo; T.e[0][4]=0;
		T.e[1][0]=0; T.e[1][1]=bx; T.e[1][2]=ay*bx%oo; T.e[1][3]=ay*bx%oo; T.e[1][4]=0;
		T.e[2][0]=0; T.e[2][1]=0; T.e[2][2]=ax*bx%oo; T.e[2][3]=ax*bx%oo; T.e[2][4]=0;
		T.e[3][0]=0; T.e[3][1]=0; T.e[3][2]=0; T.e[3][3]=1; T.e[3][4]=0;
		T.e[4][0]=ay; T.e[4][1]=by; T.e[4][2]=ay*by%oo; T.e[4][3]=ay*by%oo; T.e[4][4]=1;
		S=matrix(0);
		S.e[0][0]=ao; S.e[0][1]=bo; S.e[0][2]=ao*bo%oo; S.e[0][3]=ao*bo%oo; S.e[0][4]=1;
		T=T^(n-1);
		S=S*T;
		printf("%I64d\n",S.e[0][3]);
	}
	return 0;
}