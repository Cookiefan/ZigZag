#include <bits/stdc++.h>
#define maxn 1020
using namespace std;

int a[maxn][maxn];
vector<int> r[maxn];
int n,m,p;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		memset(a, 0, sizeof(a));
		scanf("%d",&p);
		int x, y;
		for (int i=1;i<=p;i++)
		{
			scanf("%d%d",&x,&y);
			a[x][y]=1;
		}
		for (int i=0;i<n;i++)
		{
			int now=0;
			r[i].clear();
			for (int j=0;j<m;j++)
			{
				if (a[i][j]==0) now++;
				else if (now>0)
				{
					//cout<<now<<endl;
					r[i].push_back(now);
					now=0;
				}
			}
			if (now>0)
				r[i].push_back(now);
		}
		int ans1=0, ans2=0;
		for (int i=0;i<n;i++)
		{
			for (int y:r[i])
			{
				if (y%2==0) ans1+=y/2, ans2+=y/3+(y%3!=0);
				else ans1+=y/2+1, ans2+=y/3+(y%3!=0);
			}
		}
		printf("Case #%d: %d %d\n", o, ans1, ans2);
	}


	return 0;
}