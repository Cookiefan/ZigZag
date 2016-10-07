#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long LL;

int ms;

struct matrix
{
	LL e[102][102];
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
	matrix operator *(const matrix &b)const{
		matrix c;
		for (int k=0;k<ms;k++)
			for (int i=0;i<ms;i++)if(e[i][k])
				for (int j=0;j<ms;j++)if(b.e[k][j])
					c.e[i][j]+=e[i][k]*b.e[k][j];
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

void write(matrix &a)
{
	for (int i=0;i<ms;i++)
	{
		for (int j=0;j<ms;j++)
			cout<<a.e[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl;
}

int n,m,p;

int main()
{
	//freopen("E.in","r",stdin);
	while(scanf("%d%d%d",&n,&m,&p)&&(n+m+p)!=0)
	{
		ms=n+1;
		matrix S, T, R;
		S.e[0][0]=1;
		T=matrix(1);
		int x, y; char sign;
		for (int i=1;i<=p;i++)
		{
			R.fill(1);
			scanf(" %c",&sign);
			if (sign=='g'){
				scanf("%d",&x);
				R.e[0][x]=1;
			}
			else if (sign=='e'){
				scanf("%d",&x);
				R.e[x][x]=0;
			}
			else{
				scanf("%d%d",&x,&y);
				R.e[x][x]=R.e[y][y]=0;
				R.e[x][y]=R.e[y][x]=1;
			}
			T=T*R;
		}
		T=T^m;
		S=S*T;
		for (int i=1;i<=n;i++)
			printf(i<n?"%lld ":"%lld\n",S.e[0][i]);
	}
	return 0;
}