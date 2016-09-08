#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 1200
using namespace std;

int num[15];
int f[maxn][maxn];
int n;

int main()
{
	num[1]=2;
	for (int i=2;i<=10;i++)
		num[i]=num[i-1]*2;
	f[1][1]=1;
	for (int i=2;i<=num[10];i++)
		for (int j=1;j<=i;j++)
			f[i][j]=(f[i-1][j-1]!=f[i-1][j]);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		
		for (int i=1;i<=num[n];i++)
		{
			for (int j=1;j<=num[n]-i;j++)
				cout<<' ';
			for (int j=1;j<i;j++)
				if (f[i][j])
					cout<<'o'<<' ';
				else
					cout<<' '<<' ';
			cout<<'o'<<endl;
		}
		cout<<endl;
	}
	return 0;
}