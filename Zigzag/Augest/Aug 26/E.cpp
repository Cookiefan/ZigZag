#include <bits/stdc++.h>
#define maxn 222
#define inf 5000000005L
using namespace std;

struct point
{
	int x, y;
	point(){}
	point(int x, int y):x(x),y(y){}
};
vector<point> p;
typedef long long LL;
int n,m;
int vis[maxn];
LL dis[maxn];

LL count(int i, int j)
{
	return ((LL)abs(p[i].x-p[j].x)+(LL)abs(p[i].y-p[j].y));
}

LL solve(int st)
{
	//cout<<"st: "<<st<<endl;
	memset(vis,0,sizeof(vis));
	vis[st]=1;
	for (int i=0;i<n;i++) dis[i]=count(i, st);
	dis[n]=0;
	for (int i=1;i<m;i++)
	{
		int k=n;
		for (int j=0;j<n;j++)
			if (!vis[j] && dis[j]>dis[k])
				k=j;
		//cout<<k<<endl;
		vis[k]=1;
		for (int j=0;j<n;j++)
			dis[j]=min(dis[j], count(k, j));
	}
	LL tmp=0;
	for (int i=0;i<n;i++)
		if (!vis[i])
			tmp=max(tmp, dis[i]);
	return tmp;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y;
		p.clear();
		for (int i=0;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			p.push_back(point(x,y));
		}
		LL ans=inf;
		for (int i=0;i<n;i++)
			ans=min(ans, solve(i));
		printf("Case #%d: %I64d\n",o,ans);
	}
	return 0;
}