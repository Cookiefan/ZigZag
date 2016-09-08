#include <bits/stdc++.h>
#define maxn 120
using namespace std;
int a[maxn][maxn];
int v[6];
char c;
int n,mx;

struct point
{
	int x,y;
	point(){}
	point(int x, int y):x(x),y(y){}
};

bool judge()
{
	if (v[3]) return 0;
	switch (v[1]+v[2]+v[4])
	{
		case 9:
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					if (a[i][j]==4 && a[i-1][j]==2 && a[i][j-1]==2 && a[i+1][j]==2 && a[i][j+1]==2 && 
						a[i-1][j-1]==1 && a[i-1][j+1]==1 && a[i+1][j-1]==1 && a[i+1][j+1]==1)
						return 1;
			return 0;
		break;
		case 12:
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
				{
					for (int k=i+2;k<=n;k++)
						if (a[i][j]==2 &&  a[i][j+1]==1 && a[i][j-1]==1  &&
							a[i-1][j]==2 && a[i-1][j+1]==1 && a[i-1][j-1]==1 &&
							a[k][j]==2 &&  a[k][j+1]==1 && a[k][j-1]==1  &&
							a[k-1][j]==2 && a[k-1][j+1]==1 && a[k-1][j-1]==1)
							return 1;
					for (int k=j+2;k<=n;k++)
						if (a[i][j]==2 &&  a[i+1][j]==1 && a[i-1][j]==1  &&
							a[i][j-1]==2 && a[i+1][j-1]==1 && a[i-1][j-1]==1 &&
							a[i][k]==2 &&  a[i+1][k]==1 && a[i-1][k]==1  &&
							a[i][k-1]==2 && a[i+1][k-1]==1 && a[i-1][k-1]==1)
							return 1;
				}
		break;
		case 16:
			vector<point> q;
			q.clear();
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					if (a[i][j]==1 && a[i+1][j]==1 && a[i][j+1]==1 && a[i+1][j+1]==1)
						q.push_back(point(i,j));
			if (q.size()==4 && q[1].x==q[0].x && q[2].y==q[0].y && q[3].x==q[2].x && q[3].y==q[1].y)
				return 1;
		break;
	}
	return 0;
}

int main()
{
	scanf("%d",&n);
	memset(v,0,sizeof(v));
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			scanf(" %c",&c);
			a[i][j]=c-'0';
			v[a[i][j]]++;
		}
	}
	if (judge()) printf("Yes\n");
	else printf("No\n");
	return 0;
}