#include <bits/stdc++.h>
#define maxn 120
#define maxm 5200
using namespace std;

struct point
{
	int x,y;
	point(){}
	point(int x, int y):x(x),y(y){}
	friend point operator +(point a, point b){ return point(a.x+b.x, a.y+b.y); }
}p[maxm];
const point dir[4]={point(0,1), point(1,0), point(0,-1), point(-1,0)};
int a[maxn][maxn], vis[maxn][maxn];
int n, m, tot;
char c;
vector<point>vt;

int color(point st, int col)
{
	deque<point> que;
	que.push_back(st);
	vis[st.x][st.y]=1;
	int flag=1;
	while (!que.empty())
	{
		point now=que.front();
		vt.push_back(now);
		que.pop_front();
		for (int i=0;i<4;i++)
		{
			point tmp=now+dir[i];
			if (a[tmp.x][tmp.y]==1) flag=0;
			if (!vis[tmp.x][tmp.y] && a[tmp.x][tmp.y]==col)
			{
				que.push_back(tmp);
				vis[tmp.x][tmp.y]=1;
			}
		}
	}
	return flag;
}

int judge()
{
	memset(vis,0,sizeof(vis));
	int tmp=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (!vis[i][j] && a[i][j])
			{
				color(point(i,j), 1);
				tmp++;
			}
	return tmp;
}

int main()
{
	memset(a,0,sizeof(a));
	scanf("%d%d",&n,&m);
	tot=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&c);
			if (c=='#') a[i][j]=0;
			else if (c=='.') a[i][j]=1;
			else
			{
				a[i][j]=2;
				p[++tot]=point(i,j);
			}
		}
	for (int k=1;k<=tot;k++)
		if (!vis[p[k].x][p[k].y])
		{
			vt.clear();
			if (color(p[k], 2))
			{
				int ss=vt.size();
				for (int i=0;i<ss;i++)
					a[vt[i].x][vt[i].y]=0;
			}
		}
	tot=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[i][j]==2)
				p[++tot]=point(i,j);
	for (int i=1;i<=tot;i++) a[p[i].x][p[i].y]=1;
	if (judge()==1)
	{
		int flag=1;
		for (int i=1;i<=tot;i++)
		{
			a[p[i].x][p[i].y]=0;
			if (judge()==1)
			{
				flag=0;
				break;
			}
			a[p[i].x][p[i].y]=1;
		}
		if (flag)
			for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
					if (a[i][j]) printf(j==m?".\n":".");
					else printf(j==m?"#\n":"#");
		else printf("Ambiguous\n");
	}
	else printf("Impossible\n");
	return 0;
}