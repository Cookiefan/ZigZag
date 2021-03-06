#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int v[maxn][maxn][4];
int mp[maxn][maxn][4];
struct point
{
	int x, y, z;
	point(){}
	point(int x, int y, int z):x(x),y(y),z(z){}
	friend point operator +(point a, point b)
	{
		return point(a.x+b.x, a.y+b.y, (a.z+b.z)%4);
	}
	friend bool operator ==(point a, point b)
	{
		return a.x==b.x && a.y==b.y;
	};
}st, ed;
const point dir[5]={point(-1,0,0), point(0,1,0), point(1,0,0), point(0,-1,0), point(0, 0, 1)};
deque<point> q;
deque<int> step;
int n,m;
char c;

int tran(char c)//0 door
{
	if (c=='+') return 0;
	if (c=='L') return 8;
	if (c=='D') return 4;
	if (c=='R') return 2;
	if (c=='U') return 1;
	if (c=='-') return 5;
	if (c=='|') return 10;
	if (c=='^') return 14;
	if (c=='>') return 13;
	if (c=='v') return 11;
	if (c=='<') return 7;
	else return 15;
}

bool judge(point a, point b, int e)
{
	if (e==4) return 1;
	if (!(1<=b.x && b.x<=n && 1<=b.y && b.y<=m)) return 0;
	int k=a.z;
	if (!mp[a.x][a.y][(e+4-k)%4] && !mp[b.x][b.y][(e+6-k)%4]) return 1;
	return 0;
}

int travel(point st, point ed)
{
	memset(v,0,sizeof(v));
	q.push_back(st);
	step.push_back(0);
	v[st.x][st.y][st.z]=1;
	while (!q.empty())
	{
		point now=q.front();
		//cout<<now.x<<' '<<now.y<<' '<<now.z<<endl;
		int s=step.front();
		if (now==ed) return s;
		q.pop_front();
		step.pop_front();
		for (int i=0;i<5;i++)
		{
			point tmp=now+dir[i];
			if (judge(now, tmp, i) && !v[tmp.x][tmp.y][tmp.z]  )
			{
				q.push_back(tmp);
				step.push_back(s+1);
				v[tmp.x][tmp.y][tmp.z]=1;
			}
		}
	}
	return -1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&c);
			int mask=tran(c);
			for (int k=0;k<4;k++)
				mp[i][j][k]=(mask>>k)&1;
			// for (int k=3;k>=0;k--)
			// 	cout<<mp[i][j][k]<<' ';
			// cout<<endl;
		}
	int x,y;
	scanf("%d%d",&x,&y);
	st=point(x,y,0);
	scanf("%d%d",&x,&y);
	ed=point(x,y,0);
	printf("%d\n",travel(st, ed));
	return 0;
}