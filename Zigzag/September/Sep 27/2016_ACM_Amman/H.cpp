#include <bits/stdc++.h>
#define maxn 100200
using namespace std;

int a[maxn];
int s[maxn];
int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		char c;
		for (int i=1;i<=n;i++)
		{
			scanf(" %c",&c);
			a[i]=c-'0';
		}
		int tmp=0, flag=0;
		for (int i=1;i<=n;i++)
		{
			if (a[i]==0)
			{
				tmp++;
				if (tmp>m) flag=1;
			}
			else
				tmp=0;
		}
		printf(flag?"yes\n":"no\n");
	}

	return 0;
}