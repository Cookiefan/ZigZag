#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define maxn 10020
#define inf 999999999
using namespace std;

struct edge
{
	int t, val;
	edge(){}
	edge(int t, int val):t(t),val(val){}
};
vector<edge> e[maxn];
vector<int> q;

int size[maxn], mx_size[maxn], dep[maxn], vis[maxn];
int n, rot, m, ans;

void chose(int x, int fa, int num)
{
	size[x]=1; mx_size[x]=0;
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y] && y!=fa)
		{
			chose(y, x, num);
			size[x]+=size[y];
			mx_size[x]=max(mx_size[x], size[y]);
		}
	}
	mx_size[x]=max(mx_size[x], num-size[x]);
	if (mx_size[x]<mx_size[rot]) rot=x;
}

int chose_rot(int x, int num)
{
	rot=0;
	chose(x, 0, num);
	return rot;
}

void get_dep(int x, int fa)
{
	q.push_back(dep[x]);
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y] && y!=fa)
		{
			dep[y]=dep[x]+e[x][j].val;
			get_dep(y, x);
		}
	}
}

int get_ans(int x, int h)
{
	q.clear();
	dep[x]=h;
	get_dep(x, 0);
	sort(q.begin(), q.end());
	int l=0, r=q.size()-1,tmp=0;
	while (l<r)
	{
		if (q[l]+q[r]<=m) tmp+=(r-l), l++;
		else r--;
	}
	return tmp;
}

void solve(int x)
{
	vis[x]=1;
	ans+=get_ans(x, 0);
	for (int j=0;j<e[x].size();j++)
	{
		int y=e[x][j].t;
		if (!vis[y])
		{
			ans-=get_ans(y, dep[y]);
			solve(chose_rot(y, size[y]));
		}
	}
}

void init()
{
	for (int i=1;i<=n;i++) e[i].clear();
	memset(vis,0,sizeof(vis));
	ans=0;
	mx_size[0]=inf;
}

int main()
{
	while (scanf("%d%d",&n,&m) && (n+m)!=0)
	{
		int x,y,z;
		init();
		for (int i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			e[x].push_back(edge(y,z));
			e[y].push_back(edge(x,z));
		}		
		solve(chose_rot(1, n));
		printf("%d\n",ans);
	}
	return 0;

}

