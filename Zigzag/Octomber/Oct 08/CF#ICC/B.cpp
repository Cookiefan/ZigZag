#include <bits/stdc++.h>
using namespace std;

int a[50][50];
int n,m;
int ans;

int up()
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]!=j)
				return 0;
	return 1 ;
}


void write()
{
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			cout<<a[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl;
}

int judge()
{
	if (up()) return 1;
	for (int l=1;l<=m;l++)
		for (int r=l+1;r<=m;r++)
		{
			for (int i=1;i<=n;i++)
				swap(a[i][l], a[i][r]);
			if (up()) return 1;
			for (int i=1;i<=n;i++)
				swap(a[i][l], a[i][r]);
		}
	return 0;
}

void dfs(int k)
{
	if (k>n)
	{
		// cout<<judge()<<endl;
		if (judge()) ans=1;
		return ;
	}
	dfs(k+1);
	for (int i=1;i<m;i++)
	{
		swap(a[k][i], a[k][i+1]);
		dfs(k+1);
		if (ans) return ;
		swap(a[k][i], a[k][i+1]);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	ans=0;
	dfs(1);
	if (ans) printf("YES\n");
	else printf("NO\n");
	return 0;
}