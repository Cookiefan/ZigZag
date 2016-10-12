#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

#define inf 9999999
#define maxn 5020

typedef unsigned long long LL ;
LL f[maxn], g[maxn];

int main()
{
	int n=5000;
	f[1]=f[2]=f[3]=1;
	g[1]=g[2]=g[3]=1;
	for (int i=4;i<=n;i++)
	{
		g[i]=0;
		for (int j=2;j<=i-1;j++)
			g[i]+=f[j]*f[i-j+1];
		f[i]=g[i];
		for (int j=2;j<=i-2;j++)
			f[i]+=f[j]*g[i-j+1];
	}
	while (scanf("%d",&n)!=EOF)
	{
		cout<<f[n]<<endl;
	}
	return 0;
}