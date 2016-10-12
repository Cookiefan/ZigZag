#include <bits/stdc++.h>
using namespace std;

int a[50][50];
int n,m;
int ans;

bool up()
{
	for (int i=1;i<=n;i++)
	{
		int tmp=0;
		for (int j=1;j<=m;j++)
			if (a[i][j]!=j) tmp++;
		if (tmp>2) return 0;
	}
	return 1;
}

bool judge(int x, int y)
{
	bool tmp=0;
	for (int i=1;i<=n;i++)
		swap(a[i][x], a[i][y]);
	if (up()) tmp=1;
	for (int i=1;i<=n;i++)
		swap(a[i][x], a[i][y]);
	return tmp;
}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	ans=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
			if (judge(i, j))
				ans=1;
	if (ans) printf("YES\n");
	else printf("NO\n");
	return 0;
}