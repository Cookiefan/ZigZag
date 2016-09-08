#include <bits/stdc++.h>
using namespace std;

int n,m,p;
int col[5200][5200];
int vis[3][5200];
int ope[3][5200];

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	int s,x,y;
	for (int i=1;i<=p;i++)
	{
		scanf("%d%d%d",&s,&x,&y);
		vis[s][x]=i;
	}
	for (int i=1;i<=p;i++)
	{
		
		vis[s][x]=i;
	}

	return 0;
}