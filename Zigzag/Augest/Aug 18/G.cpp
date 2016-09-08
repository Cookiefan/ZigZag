#include <bits/stdc++.h>
#define maxn 200020
#define nb 22
using namespace std;

typedef long long llg;
const llg oo=1000000007;

struct matrix
{
	llg e[nb][nb];
	matrix()
	{
		memset(e,0,sizeof(e));
	}
	matrix(int x)
	{
		memset(e,0,sizeof(e));
		for (int i=0;i<nb;i++) e[i][i]=x;
	}
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int k=0;k<nb;k++)
			for (int i=0;i<nb;i++)
				for (int j=0;j<nb;j++)
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
}S,T;

int n,m,k;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&k);
		S.clear();
		T.clear();
		S.e[0][0]=1;
		for (int i=0;i<=m-1;i++) T.e[i][0]=k*(k-1);
		for (int i=m;i<=2*m;i++) T.e[i][m]=k*(k-1);
		for (int i=0;i<m-1;i++)
			T.e[i][i+1]=k;
		T.e[m-1][2*m]=k;
		for (int i=m;i<=2*m-1;i++) T.e[i][i+1]=k;
		T=T^n;
		// for (int i=0;i<=2*m;i++)
		// {
		// 	for (int j=0;j<=2*m;j++)
		// 		printf("%d ",T.e[i][j]);
		// 	printf("\n");
		// }
		S=S*T;
		llg ans=0;
		for (int i=m;i<=2*m;i++)
			(ans+=S.e[0][i])%=oo;
		printf("%d\n",ans);
	}
	return 0;
}