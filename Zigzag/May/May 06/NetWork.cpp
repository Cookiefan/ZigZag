#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 12000
using namespace std;
typedef long long llg;

class matrix
{
public:
	double e[maxn][maxn];
	int size;
	matrix(){}
	matrix(int num):size(num)
	{
		memset(e,0,sizeof(e));
	}
	matrix(int num,int x):size(num)
	{
		memset(e,0,sizeof(e));
		for (int i=0;i<size;i++) e[i][i]=x;
	}
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c=matrix(a.size);
		for (int k=0;k<c.size;k++)
			for (int i=0;i<c.size;i++)
				for (int j=0;j<c.size;j++)
					c.e[i][j]+=a.e[i][k]*b.e[k][j];
		return c;
	}
	friend matrix operator ^(matrix e, llg k)
	{
		matrix tmp=matrix(e.size, 1);
		while (k)
		{
			if (k&1) tmp=tmp*e;
			k=k>>1;
			e=e*e;
		}
		return tmp;
	}
};

int t[maxn][maxn];
int n;

int main()
{
	matrix F, A;
	scanf("%d"&n);//读入城市数
	for (int i=0;i<n;i++)//读入每个城市初始人口数
		scanf("%d",&A.e[i][0]);
	for (int i=0;i<n;i++)//读入城市人口迁移率矩阵
		for (int j=0;j<n;j++)
			scanf("%lf",&F.e[i][j]);//F.e[i][j]表示i城市向j城市的迁移率
	scanf("%d",&day);//读入迭代次数
	A=A^day;
	for (int i=0;i<n;i++)
		printf("The population of the city %d is :%.0f\n", i+1, A.e[i][0]);
	return 0;
  }