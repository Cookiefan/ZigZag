#include <bits/stdc++.h>
#define maxn 320
using namespace std;

int a[maxn][maxn], vis[maxn][maxn];
int sum[maxn], id[maxn];
int n,m,k,num;

struct point
{
	int x,y;
	point (){}
	point (int x, int y):
	x(x), y(y){}
};
const point dir[4]={point(0,1),point(1,0),point(0,-1),point(-1,0)};
point operator +(point a, point b)
{
	return point(a.x+b.x, a.y+b.y);
}
queue<point>q;
vector<point> p[maxn];
int bfs(point st, int col)
{
	while (!q.empty()) q.pop();
	q.push(st);
	vis[st.x][st.y]=1;
	bool flag=1;
	int cnt=0;
	p[col].clear();
	while (!q.empty())
	{
		point now=q.front();
		cnt++;
		q.pop();
		p[col].push_back(now);
		if (now.x==1 || now.x==n || now.y==1 || now.y==m)
			flag=0;
		for (int i=0;i<4;i++)
		{
			point tmp=now+dir[i];
			if (a[tmp.x][tmp.y] && !vis[tmp.x][tmp.y])
			{
				q.push(tmp);
				vis[tmp.x][tmp.y]=1;
			}
		}
	}
	if (flag) return cnt;
	else return -1;
}

bool cmp(int a, int b)
{
	return sum[a]<sum[b];
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	char c;
	memset(a,0,sizeof(a));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&c);
			if (c=='*') a[i][j]=0;
			else a[i][j]=1;
		}
	memset(vis,0,sizeof(vis));
	num=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (!vis[i][j] && a[i][j])
			{
				int tmp=bfs(point(i, j), num+1);
				if (tmp!=-1)
					sum[++num]=tmp;
			}

	for (int i=1;i<=num;i++) id[i]=i;
	sort(id+1, id+1+num, cmp);
	int ans=0;
	for (int i=1;i<=num-k;i++)
	{
		ans+=sum[id[i]];
		for (point t:p[id[i]]) a[t.x][t.y]=0;
	}
	printf("%d\n", ans);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			printf(a[i][j]?".":"*");
		printf("\n");
	}
	return 0;
}