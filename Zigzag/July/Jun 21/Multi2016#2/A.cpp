#include <bits/stdc++.h>
#define maxn 120000

int w[maxn];
int n;
long long s1, s2, up, dw;

long long gcd(long long a, long long b)
{
	return (!a)?b:gcd(b%a, a);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&w[i]);
		s1=0; s2=0;
		for (int i=1;i<=n;i++)
		{
			s1+=abs(w[i]);
			s2+=w[i]*w[i];
		}
		dw=4*n;
		up=(long long)4*n*s2-(long long)(2*s1)*(2*s1);
		printf("%I64d/%I64d\n",up/gcd(up,dw),dw/gcd(up,dw));
	}
	return 0;
}