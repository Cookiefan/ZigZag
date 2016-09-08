#include <bits/stdc++.h>
#define maxn 12
using namespace std;

int a[maxn][maxn];
int f[1200][1200][12];
vector<int> imsk[12];
int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	int x,y;
	memset(a,0,sizeof(a));
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		a[x][y]=1;
	}
	int mxmsk=1<<n;
	for (int st=1;st<=n;st++)
		for (int i=0;i<2*n;i++)
		{
			int b=i/2+i%2, w=i/2, col=i%2;
			int sb=imask[b].size(), sw=imask[w].size();
			for (int x=0;x<sb;x++)
				for (int y=0;y<sw;y++)
					for (int j=0;j<n;j++)
					{
						if (col==0)
						{
							if (!((x>>(j-1))&1))
								f[x | (1<<(j-1))][y]=min(f[x | (1<<(j-1))][y], f[x][y]+)
						}
						else
						{
							if (!((y>>(j-1))&1))
						}
					}
		}




	return 0;
}