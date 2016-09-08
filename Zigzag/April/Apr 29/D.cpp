#include <bits/stdc++.h>
#define maxn 220000
using namespace std;

struct point
{
	int x,y,id;
	point(){}
	point(int x,int y, int id):x(x),y(y),id(id){}
	friend bool operator <(point a, point b) { return a.x<b.x; }
}p[maxn];

struct mx_bit
{
	int mx[maxn],key[maxn];
	int num;
	void cov(int x,int z)
	{
		key[x]=z;
		for (int i=x;i<=num;i+=(i&-i)) mx[i]=max(mx[i],z);
	}
	int ask(int l,int r)
	{
		if (l>r) swap(l,r);
		int tmp=-1;
		while (l<=r)
		{
			tmp=max(tmp,key[r]);
			for (r-=1;r-(r&-r)>=l;r-=(r&-r)) tmp=max(tmp,mx[r]);
		}
		return tmp;
	}
	void init(int x)
	{
		num=x;
		memset(mx,-1,sizeof(mx));
		memset(key,-1,sizeof(key));
	}
}tree;
int ans[maxn];
int n;

int get_ans(int k, int h)
{
	int l=1, r=k-1, tmp1=-1;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (tree.ask(k-1, mid)>=h)
		{
			l=mid+1;
			tmp1=mid;
		}
		else
			r=mid-1;
	}
	l=k+1, r=n;
	int tmp2=-1;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (tree.ask(k+1, mid)>=h)
		{
			r=mid-1;
			tmp2=mid;
		}
		else
			l=mid+1;
	}
	//cout<<tmp1<<' '<<tmp2<<' ';
	if (tmp1==-1 && tmp2==-1) return 0;
	else if (tmp1==-1) return tmp2;
	else if (tmp2==-1) return tmp1;
	else if (p[k].x-p[tmp1].x==p[tmp2].x-p[k].x) return (p[tmp1].y>p[tmp2].y)?tmp1:tmp2;
	else return (p[k].x-p[tmp1].x<p[tmp2].x-p[k].x)?tmp1:tmp2;
}

int main()
{
	scanf("%d",&n);
	int x,y;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&x, &y);
		p[i]=point(x,y,i);
	}
	sort(p+1,p+n+1);
	tree.init(n+1);
	for (int i=1;i<=n;i++) tree.cov(i, p[i].y);
	p[0].id=-1;
	for (int i=1;i<=n;i++)
		ans[p[i].id]=p[get_ans(i, p[i].y)].id;
	for (int i=1;i<=n;i++)
		printf(i==n?"%d\n":"%d ",ans[i]);
	return 0;
}