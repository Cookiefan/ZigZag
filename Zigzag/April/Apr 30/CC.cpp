#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
int x[maxn],y[maxn];
int fa[maxn][50], f[maxn];
int n,m, tot;

int find(int x)
{
	return (f[x]?x:f[x]=find(f[x]));
}
bool merge(int x,int y)
{
	int fx=find(x), fy=find(y);
	if (fx!=fy)
	{
		f[fx]=fy;
		return 1;
	}
	return 0;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int t, x, y;
		tot=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&t, &x, &y);
			if (t==1)
			{
				if (merge(x,y));
			}
			else x[++tot]=x, y[++tot]=y;
		}


	}
	return 0;

}