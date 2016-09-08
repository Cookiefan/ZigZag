#include <bits/stdc++.h>
#define maxn 2200000
using namespace std;
struct query
{
	int tp, x, y, h;
	query(){}
	query(int t, int x, int y, int h):tp(t),x(x),y(y),h(h){}
}q[maxn], q1[maxn], q2[maxn];
int f[100][maxn], ans[maxn];
int n,m;

int find(int dep, int x)
{
	return (!f[dep][x])?x:f[dep][x]=find(dep, f[dep][x]);
}

void merge(int dep, int x, int y)
{
	int fx=find(dep, x), fy=find(dep, y);
	if (fx!=fy) f[dep][fx]=fy;
}

void solve(int l, int r, int st, int ed, int dep)
{
	if (st>ed) return ;
	if (l==r)
	{
		for (int i=st;i<=ed;i++)
		{
			if (q[i].tp==1) ans[q[i].h]=-1;
			if (q[i].tp==2) ans[q[i].h]=l;
		}
		return ;
	} 
	int mid=(l+r)>>1, l1=0, l2=0;
	for (int i=st;i<=ed;i++)
		if (q[i].tp==1)
		{
			if (q[i].h<=mid)
			{
				merge(dep, q[i].x, q[i].y);
				q1[++l1]=q[i];
			}
			else
				q2[++l2]=q[i];
		}
	for (int i=st;i<=ed;i++)
		if (q[i].tp==2)
		{
			if (find(dep, q[i].x)==find(dep, q[i].y))
				q1[++l1]=q[i];
			else
				q2[++l2]=q[i];
		}
	for (int i=st;i<=ed;i++)
		if (q[i].tp==1)
			merge(dep, q[i].x, q[i].y);	
	for (int i=1;i<=l1;i++) q[st+i-1]=q1[i];
	for (int i=1;i<=l2;i++) q[st+l1+i-1]=q2[i];
	solve(l, mid, st, st+l1-1, dep+1);
	solve(mid+1, r, st+l1, ed, dep+1);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x,y,t;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&t,&x,&y);
			q[i]=query(t,x,y,i);
		}
		memset(f,0,sizeof(f));
		memset(ans,0,sizeof(ans));
		solve(0,m,1,m,1);
		for (int i=1;i<=m;i++)
			if (ans[i]!=-1)
			{
				if (ans[i]>=i) printf("%d\n",-1);
				else printf("%d\n", ans[i]);
			}
	}
	return 0;
}
/*
2
4 5
1 1 2
2 1 2
1 2 3
2 1 3
2 1 4
5 10
1 1 5
2 1 5
1 2 5
2 1 2
1 4 5
2 1 4
1 3 5
2 1 5
2 3 4
2 2 3
*/
