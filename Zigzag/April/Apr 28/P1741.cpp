#include <bits/stdc++.h>
#define maxn 12000
#define inf 99999999
using namespace std;

struct edge
{
	int s,t,val;
	edge(){}
	edge(int s, int t, int val):s(s),t(t),val(val){}
};

vector<edge> e[maxn];
vector<int> q;
int vis[maxn], size[maxn], mx_size[maxn], dep[maxn];
int n, m, rot, ans;

void choose(int x, int fa, int sum)//递归寻找重心
{
	size[x]=1;
	int ss=e[x].size();
	for (int i=0;i<ss;i++)
	{
		int y=e[x][i].t;
		if (!vis[y] && y!=fa) choose(y, x, sum);
		size[x]+=size[y];
		mx_size[x]=max(mx_size[x], size[y]);
	}
	mx_size[x]=max(mx_size[x], sum-size[x]);
	if (mx_size[x]<mx_size[rot]) rot=x;
}

void get_deep(int x, int fa)//递归求每个点的深度
{
	q.push_back(dep[x]);
	int ss=e[x].size();
	for (int i=0;i<ss;i++)
	{
		int y=e[x][i].t;
		if (!vis[y] && y!=fa)
		{
			dep[y]=dep[x]+e[x][i].val;
			get_deep(y, x);
		}
	}
}

int get_ans(int x)//计算当前结点为根的答案
{	
	q.clear();
	get_deep(x, 0);
	sort(q.begin(), q.end());
	int l=0, r=q.size()-1, tmp=0;
	while (l<r)
	{
		if (q[l]+q[r]<=m) tmp+=(r-l), l++;
		else r--;
	}
	return tmp;
}

void solve(int x)//分治处理x为根的子树
{
	rot=0;
	chose(x, 0, n);//重定根 
	vis[rot]=1;
	dep[rot]=0;
	ans+=get_ans(rot);
	int ss=e[rot].size();
	for (int i=0;i<ss;i++)
	{
		int y=e[x][i].t;
		if (!vis[y]) ans-=get_ans(y);
		solve(y);
	}
}

int main()
{
	while (scanf("%d%d",&n,&m) && (n+m)!=0)
	{
		int x,y,z;
		for (int i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			e[x].push_back(edge(x,y,z));
			e[y].push_back(edge(y,x,z));
		}
		ans=0;
		mx_size[0]=inf;
		solve(1);
		printf("%d\n",ans);
	}
	return 0;
}