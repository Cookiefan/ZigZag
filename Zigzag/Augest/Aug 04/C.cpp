#include <bits/stdc++.h>
#define maxn 1200000
using namespace std;
int n;
int a[maxn],b[maxn];

int count(int x)
{
	int tmp=0;
	while (x)
	{
		tmp+=(x&1);
		x=x>>1;
	}
	return tmp;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int ans=0, rev=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			ans^=a[i];
			if (count(a[i])>2)
				rev^=1;
		}
		if (ans || (!ans && rev)) printf("First player wins.\n");
		else printf("Second player wins.\n");
	}
	return 0;
}