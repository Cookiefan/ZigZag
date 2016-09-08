#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 2200
#define oo 1000000007
using namespace std;
long long f[maxn][6];
long long ans[maxn];
int n;

int main()
{
	f[1][1]=26;
	ans[1]=26;
	for (int i=2;i<=2000;i++)
	{
		f[i][1]=(ans[i-1]*25)%oo;
		f[i][2]=f[i-1][1];
		f[i][3]=f[i-1][2];
		ans[i]=(f[i][1]+f[i][2]+f[i][3])%oo;
	}
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		printf("%I64d\n",ans[n]);
	}	
	return 0;
}