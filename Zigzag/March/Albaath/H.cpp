#include <bits/stdc++.h>
#define maxn 120
using namespace std;
int mp[maxn][maxn],last[maxn][maxn],vis[maxn][maxn];
int n,m;

struct point
{
	int x,y;
	point(){}
	point (int x,int y):x(x),y(y){}
	friend point operator +(point a,point b)
	{
		return point(a.x+b.x, a.y+b.y);
	}
	friend bool operator ==(point a,point b)
	{
		return a.x==b.x && a.y==b.y;
	}
}st,ed;
const point dir[4]={point(0,1), point(1,0), point(0,-1), point(-1,0),};
vector<point> a;
deque<point> que;

void cover()
{
	que.clear();
	memset(last,0,sizeof(last));
	int num=a.size();
	for (int i=0;i<num;i++)
	{
		que.push_back(a[i]);
		last[a[i].x][a[i].y]=1;
	}
	while (!que.empty())
	{
		point now=que.front();
		que.pop_front();
		for (int i=0;i<4;i++)
		{
			point tmp=now+dir[i];
			if (!last[tmp.x][tmp.y] && mp[tmp.x][tmp.y])
			{
				last[tmp.x][tmp.y]=last[now.x][now.y]+1;
				que.push_back(tmp);
			}
		}
	}
}

bool search()
{
	que.clear();
	memset(vis,0,sizeof(vis));
	que.push_back(st);
	vis[st.x][st.y]=1;
	while (!que.empty())
	{
		point now=que.front();
		if (now==ed) return 1;
		que.pop_front();
		for (int i=0;i<4;i++)
		{
			point tmp=now+dir[i];
			if (!vis[tmp.x][tmp.y] && mp[tmp.x][tmp.y] && (last[tmp.x][tmp.y]==0 || vis[now.x][now.y]+1<last[tmp.x][tmp.y]))
			{
				vis[tmp.x][tmp.y]=vis[now.x][now.y]+1;
				que.push_back(tmp);
			}
		}
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
		char c;
		a.clear();
		memset(mp,0,sizeof(mp));
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				scanf(" %c",&c);
				if (c=='#') mp[i][j]=0; else mp[i][j]=1;
				if (c=='S') st=point(i,j);
				if (c=='X') ed=point(i,j);
				if (c=='*') a.push_back(point(i,j));
			}
		cover();
		// for (int i=1;i<=n;i++)
		// {
		// 	for (int j=1;j<=m;j++)
		// 		cout<<last[i][j]<<' ';
		// 	cout<<endl;
		// }
		// cout<<endl;
		if (search()) printf("yes\n");
		else printf("no\n");
		// for (int i=1;i<=n;i++)
		// {
		// 	for (int j=1;j<=m;j++)
		// 		cout<<vis[i][j]<<' ';
		// 	cout<<endl;
		// }
	}
	
	return 0;
}