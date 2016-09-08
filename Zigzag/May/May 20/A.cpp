#include <bits/stdc++.h>

using namespace std;

int v[20];
int a,b,d,n;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		memset(v,0,sizeof(v));
		scanf("%d%d%d%d",&a,&b,&d,&n);
		if (n<5)
		{
			int sum=0;
			for (int i=1;i<=n;i++)
				sum=sum*10+a;
			sum=sum*b;
			while (sum)
			{
				v[sum%10]++;
				sum=sum/10;
			}
			printf("%d\n",v[d]);
		}
		else if (a*b<10)
		{
			if (d==a*b) printf("%d\n",n);
			else printf("%d\n",0);
		}
		else
		{
			int x=a*b/10, y=a*b%10;
			if (x+y<10)
			{
				v[x]++;
				v[y]++;
				v[x+y]+=(n-1);
				printf("%d\n",v[d]);
			}
			else
			{
				int sum=a*b+a*b*10;
				int r=sum/100, s=(sum/10)%10, t=sum%10;
				v[r]++;
				v[s]++;
				v[t]++;
				if (n>1) v[s+1]+=(n-2);
				printf("%d\n",v[d]);
			}
		}
	}
	return 0;
}