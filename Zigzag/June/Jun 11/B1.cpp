#include <bits/stdc++.h>
#define maxn 12000
using namespace std;

int n,m;
int a[maxn];
int ans;

bool judge(int k)
{
	for (int i=1;i<=k/2;i++)
	{
		bool flag=1;
		for (int j=i+1;j<=i+i;j++)
			if (a[i]!=a[j])
				flag=0;
		if (flag) return 1;
	}
	return 0;
}

void dfs(int k)
{
	if (k>1 && !judge(k-1)) ans++;
	if (k==n+1) return ;
	for (int i=1;i<=m;i++)
	{
		a[k]=i;
		dfs(k+1);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	ans=0;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}