#include <bits/stdc++.h>
using namespace std;

struct point
{
	int x, y;
	point(){}
	point(int x, int y):x(x),y(y){}
	point operator +(const point &b)const{
		return point(x+b.x, y+b.y);
	}
	bool operator <(const point &b)const{
		return x==b.x?y<b.y:x<b.x;
	}
};
map<point, int> mp;
map<point, int> vis;
vector<point> q;
int n,m,num;

int main()
{
	scanf("%d%d%d",&n,&m,&num);
	int x,y ;
	for (int i=1;i<=num;i++)
	{
		scanf("%d%d",&x,&y);
		q.push_back(point(x, y));
		vis[point(x, y)]=1;
	}
	point now=point(0, 0);
	point dir=point(1, 1);
	int t=0;
	mp.clear();
	while (1)
	{
		now=now+dir;
		//cout<<now.x<<' '<<now.y<<endl;
		t++;
		if (!mp.count(now) && vis.count(now)) mp[now]=t;
		if (now.x==n && now.y==m) break;
		if (now.x==n && now.y==0) break;
		if (now.x==0 && now.y==m) break;
		if (now.x==0 && now.y==0) break;
		if (now.y==m) dir.y*=(-1);
		if (now.x==n) dir.x*=(-1);
		if (now.x==0) dir.x*=(-1);
		if (now.y==0) dir.y*=(-1);
	}
	for (int i=0;i<q.size();i++){
		if (mp.count(q[i]))
			printf("%d\n", mp[q[i]]);
		else
			printf("-1\n");
	}
	return 0;
}