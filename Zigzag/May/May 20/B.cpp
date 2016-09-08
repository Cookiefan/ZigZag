#include <bits/stdc++.h>
#define oo 1000000007

using namespace std;

long long f[2002][2002];
int num[20];
int n;

int main()
{
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for (int i=1;i<=1000;i++)
		for (int j=0;j<=i;j++)
			f[i][j]=(f[i-1][j-1]+f[i-1][j])%oo;
	num[0]=1;
	for (int i=1;i<=11;i++)
		num[i]=num[i-1]*2;
	scanf("%d",&n);
	int h;
	for (int i=1;i<=11;i++)
		if (n>=(num[i]-1))
			h=i;
	n-=(num[h]-1);
	printf("%d\n",f[num[h]][n]);
	return 0;
}