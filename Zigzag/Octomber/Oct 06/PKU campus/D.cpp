#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long LL;

const int ms=4;
const LL oo=10007;

struct matrix
{
	LL e[ms][ms];
	matrix(){
		memset(e, 0, sizeof(e));
	}
	matrix(int x){
		memset(e, 0, sizeof(e));
		for (int i=0;i<ms;i++) e[i][i]=x;
	}
	void fill(int x){
		memset(e, 0, sizeof(e));
		for (int i=0;i<ms;i++)
			e[i][i]=x;
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
	friend matrix operator ^(matrix a, int b){
		matrix tmp=matrix(1);
		while(b){
			if (b&1) tmp=tmp*a;
			b>>=1;
			a=a*a;
		}
		return tmp;
	}
};

int n;


int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		matrix S, T;
		S.e[0][0]=1;
		T=matrix(2);
		T.e[0][1]=1;
		T.e[0][2]=1;
		T.e[1][3]=1;
		T.e[1][0]=1;
		T.e[2][3]=1;
		T.e[2][0]=1;
		T.e[3][1]=1;
		T.e[3][2]=1;
		T=T^n;
		S=S*T;
		printf("%lld\n",S.e[0][0]);
	}
	return 0;
}