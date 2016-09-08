#include <bits/stdc++.h>
#define maxn 120000
#define inf 999999999
using namespace std;
int n,m,p,q;
int a[maxn], op[maxn];
char c;

int main()
{
	int now=1, sum;
	p=q=m=0;
	op[++m]=1;
	while (scanf("%c",&c) && c!='=')
	{
		if (c=='?')
		{
			if (now==1) p++;
			else q++;
		}
		else if (c=='+') now=op[++m]=1;
		else if (c=='-') now=op[++m]=-1;
	}
	scanf("%d",&n);
	if (p<=q*n+n && p*n>=q+n)
	{
		printf("Possible\n");
		if (p<=q+n)
		{
			sum=q+n;
			now=p;
			for (int i=1;i<=m;i++)
				a[i]=1;
			for (int i=1;i<=m;i++)
				if (op[i]==1)
				{
					while (now<sum && a[i]<n)
					{
						a[i]++;
						now++;
					}
				}
		}
		else
		{
			sum=p;
			now=q+n;
			for (int i=1;i<=m;i++)
				a[i]=1;
			for (int i=1;i<=m;i++)
				if (op[i]==-1)
				{
					while (now<sum && a[i]<n)
					{
						a[i]++;
						now++;
					}
				}
		}
		for (int i=1;i<=m;i++)
		{
			printf("%d ",a[i]);
			printf("%c ",i==m?'=':(op[i+1]>0?'+':'-'));
		}
		printf("%d\n",n);
	}
	else
	{
		printf("Impossible\n");
		
	}
	
	return 0;
}