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
		for (int i=0;i<ms;i++)
			for (int j=0;j<ms;j++)
				e[i][j]=0;
	}
	matrix(int x){
		for (int i=0;i<ms;i++)
			for (int j=0;j<ms;j++)
				e[i][j]=0;
		for (int i=0;i<ms;i++) e[i][i]=x;
	}
	void fill(int x){
		for (int i=0;i<ms;i++)
			for (int j=0;j<ms;j++)
				e[i][j]=0;
		for (int i=0;i<ms;i++)
			e[i][i]=x;
	}
	matrix operator *(const matrix &b)const{
		matrix c;
		for (int k=0;k<ms;k++)
			for (int i=0;i<ms;i++) if(e[i][k])
				for (int j=0;j<ms;j++) if(b.e[k][j])
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
char cmd[10];

int main()
{
	//freopen("E.in","r",stdin);
	while(scanf("%d%d%d",&n,&m,&p) &&(n+m+p)!=0)
	{
		ms=n+1;
		matrix S, T;
		S.e[0][0]=1;
		T=matrix(1);
		int x, y; char sign;
		for (int i=1;i<=p;i++)
		{
			// scanf("%s", cmd);
			// sign = cmd[0];
			scanf(" %c",&sign);
			if (sign=='g'){
				scanf("%d",&x);
				T.e[0][x]++;
			}
			else if (sign=='e'){
				scanf("%d",&x);
				for (int j=0;j<ms;j++)
					T.e[j][x]=0;
			}
			else{
				scanf("%d%d",&x,&y);
				for (int j=0;j<ms;j++)
					swap(T.e[j][x], T.e[j][y]);
			}
		}
		T=T^m;
		S=S*T;
		for (int i=1;i<=n;i++)
			printf(i<n?"%lld ":"%lld\n",S.e[0][i]);
	}
	return 0;
}