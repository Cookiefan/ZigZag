#include <bits/stdc++.h>
#define maxn 22
using namespace std;

struct matrix
{
	double e[maxn][maxn];
	matrix()
	{
		memset(e,0,sizeof(e));
	}
	matrix(double x)
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

int n,k;
double p[maxn];

int main()
{
	scanf("%d%d",&n,&k);
	matrix A, T;
	for (int i=1;i<=n;i++)
	{
		scanf("%lf",&p[i]);
		A.clear(); T.clear();
		A.e[0][0]=p[i]; A.e[0][1]=p[i];
		for (int j=2;j<=k;j++)
			A.e[0][j]=A.e[0][j-1]+(1.0-A.e[0][j-1])*p[i];
		T.e[0][0]=1;
		for (int j=2;j<=k;j++)
			T.e[j][j-1]=1;

		T.e[0][k]=1.0;
		T.e[1][k]=-(1.0-p[i]);
		T.e[k][k]=1.0-p[i];
		// for (int j=0;j<=k;j++)
		// {
		// 	for (int o=0;o<=k;o++)
		// 		cout<<T.e[j][o]<<' ';
		// 	cout<<endl;
		// }
		//for (int j=1;j<=100;j++)
		//	T=T^10;
		A=A*T*T;
		for (int i=0;i<=k;i++)
			printf("%.6f\n",A.e[0][k]);
	}
	return 0;
}