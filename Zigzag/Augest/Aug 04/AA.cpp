#include <bits/stdc++.h>
#define maxn 4
using namespace std;
typedef long long llg;
const llg oo=1000000007;
//矩阵乘法&快速幂
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
		for (int i=0;i<4;i++) e[i][i]=x;
	}
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int k=0;k<4;k++)
			for (int i=0;i<4;i++)
				for (int j=0;j<4;j++)
					(c.e[i][j]+=a.e[i][k]*b.e[k][j]%oo)%=oo;
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
	};
};

int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		matrix T,S;
		S.e[0][0]=S.e[0][1]=1;
		T.e[0][0]=m;
		T.e[0][1]=0;
		T.e[1][0]=1;
		T.e[1][1]=1;
		T=T^n;
		S=S*T;
		// for (int i=0;i<=1;i++)
		// {
		// 	for (int j=0;j<=1;j++)
		// 		cout<<T.e[i][j]<<' ';
		// 	cout<<endl;
		// }
		printf("%d\n",S.e[0][0]);
	} 
	return 0;
}