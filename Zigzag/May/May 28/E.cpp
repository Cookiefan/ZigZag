#include <bits/stdc++.h>
using namespace std;

int v[20], cof[20][20];
int sum;

void dfs(int x, int y)
{
	if (x==11 && y==1)
	{
		sum++;
		return ;
	}
	for (int i=0;i<=t;i++)
		if (!v[i] && !cof[i][a[x-1][y]] && !cof[i][a[x][y-1]])
		{
			if (i) v[i]=1;
			a[x][y]=i;
			dfs(x+(y+1)%n, y+1);
			a[x][y]=0;
			if (i) v[i]=0;
		}
}

int main()
{
	sum=0;
	dfs(1, 1);
	cout<<sum<<endl;
	return 0;
}