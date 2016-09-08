#include <bits/stdc++.h>
#define maxn 1020
using namespace std;

int mp[maxn][maxn];
int lim[maxn][maxn], vis[maxn][maxn];
struct point
{
	int x, y;
	point(){}
	point(int x, int y):x(x),y(y){}
};
point operator +(point a, point b)
{
	return point(a.x+b.x, a.y+b.y);
}
bool operator ==(point a, point b)
{
	return a.x==b.x && a.y==b.y;
}
const point dir[4]={point(0, 1), point(1, 0), point(-1, 0), point(0, -1)};
typedef pair<point,int> ppt;
deque<ppt> q;
point st,ed;
int n,m;

bool travel()
{
	memset(vis,0,sizeof(vis));
	for (int i=q.size()-1;i;i--)
		vis[q[i].first.x][q[i].first.y]=1;
	bool flag=0;
	while (!q.empty())
	{
		point now=q.front().first;
		int cur=q.front().second;
		lim[now.x][now.y]=cur;
		q.pop_front();
		if (now==ed) flag=1;
		for (int i=0;i<4;i++)
		{
			point tmp=now+dir[i];
			if (mp[tmp.x][tmp.y] && !vis[tmp.x][tmp.y] && cur+1<lim[tmp.x][tmp.y])
			{
				q.push_back(ppt(tmp, cur+1));
				vis[tmp.x][tmp.y]=1;
			}
		}
	}
	return flag;
}
int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		q.clear();
		memset(lim,0x3f,sizeof(lim));
		memset(mp,0,sizeof(mp));
		char c;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				scanf(" %c",&c);
				if (c=='F')
					q.push_back(ppt(point(i,j), 0));
				if (c=='S')
					st=point(i,j);
				if (c=='E')
					ed=point(i,j);
				if (c=='#') mp[i][j]=0;
				else mp[i][j]=1;
			}
		travel();
		q.clear();
		q.push_back(ppt(st, 0));
		printf(travel()?"Y\n":"N\n");
	}

	return 0;
}