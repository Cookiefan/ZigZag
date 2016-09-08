#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#define oo 10
#define maxn 500

using namespace std;

struct BigInt
{
	int e[100];
	void clean(){
		memset(e,0,sizeof(e));
	}
}a;

BigInt operator +(BigInt a,BigInt b)
{
	BigInt c; c.clean();
	c.e[0]=max(a.e[0],b.e[0]);
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i]+=a.e[i]+b.e[i];
		c.e[i+1]+=c.e[i]/oo;
		c.e[i]=c.e[i]%oo;
	}
	if (c.e[c.e[0]+1]) c.e[0]++;
	return c;
}

void write(BigInt a)
{
	printf("%d",a.e[a.e[0]]);
	for (int i=a.e[0]-1;i>0;i--) printf("%d",a.e[i]);
	printf("\n");
}

int n;
BigInt f[maxn];


int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		f[0].e[0]=f[0].e[1]=1;
		f[1].e[0]=f[1].e[1]=1;
		for (int i=2;i<=n;i++)
		{
			f[i]=f[i-1]+f[i-2];
		}
		write(f[n]);
	}
	return 0;
}