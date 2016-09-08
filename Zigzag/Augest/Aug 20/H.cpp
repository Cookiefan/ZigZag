#include <bits/stdc++.h>
using namespace std;

int n,m,k;
const string s="AABBAB";

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&k);
		printf("Case #%d:\n",o);
		if (k<=1 || n<=2)
		{
			if (m!=n) printf("Impossible\n");
			else
			{
				for (int i=1;i<=n;i++) printf("A");
				printf("\n");
			}
		}
		else if (k==2)
		{
			if (n<=7)
			{
				if (n!=m) printf("Impossible\n");
				else 
				{
					for (int i=1;i<=n;i++) printf("A");
					printf("\n");
				}
			}
			else if (n==8)
			{
				if (m==7) printf("AABBABAA\n");
				else if (m==8) printf("AAAAAAAA\n");
				else printf("Impossible\n");
			}
			else 
			{
				if (n==m)
				{
					for (int i=1;i<=n;i++) printf("A");
					printf("\n");
				}
				else if (m<8 || m>n) printf("Impossible\n");
				else
				{
					int tmp=m-8;
					for (int i=1;i<=tmp;i++) printf("A");
					for (int i=0;i<n-tmp;i++) printf("%c",s[i%6]);
					printf("\n");
				}
			}
		}
		else
		{
			if (m<3 || m>n) printf("Impossible\n");
			else
			{
				int tmp=m-3;
				for (int i=1;i<=n-tmp;i++) printf("%c",'A'+i%3);
				for (int i=n-tmp+1;i<=n;i++) printf("%c",'A'+(n-tmp)%3);
				printf("\n");
			}
		}
	}
	return 0;
}