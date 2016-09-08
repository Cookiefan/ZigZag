#include <bits/stdc++.h>
using namespace std;

struct query
{
	int x, y, v;
	query(){}
	query(int x, int y, int v):
	x(x),y(y),v(v){}
};
bool operator <(query a, query b)
{
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
typedef vector<query> VQ;
vector<query> p[maxn], q[maxn];
int st[2*maxn];
int n,m;

struct bit
{
	int b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}s,t;

void sadd(int x,int y,int z)
{
	s.add(x,z); s.add(y+1,-z);
	t.add(x,z*x); t.add(y+1,-z*(y+1));
}

int sask(int x,int y)
{
	int tmp=s.ask(y)*(y+1)-s.ask(x-1)*x-(t.ask(y)-t.ask(x-1));
	return tmp;
}

void modify(VQ &p, VQ &q);
{
	int n=p.size();
	for (int i=0;i<n;i++) sadd(p[i].x, p[i].y, 1);

	for (int i=0;i<n;i++) st[2*i]=p[i].x, st[2*i+1]=p[i].y;
	int m=unique(st, st+2*n)-st;
	for (int i=0;i<m-1;i++) q.push_back(query(st[i], st[i+1], sask(st[i], st[i+1])));

	for (int i=0;i<n;i++) sadd(p[i].x, p[i].y, -1);
}

int main()
{
	while (scanf("%d%d",&n,&m) && n+m)
	{
		int x, y, z, mx=0;
		for (int i=1;i<n;i++) scanf("%d%d",&x,&y);
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			p[z].push_back(query(x,y,1));
			mx=max(mx, z);
		}
		s.init(n+1);
		t.init(n+1);
		for (int i=1;i<=mx;i++) modify(p[i], q[i]);

	}


	return 0;
}