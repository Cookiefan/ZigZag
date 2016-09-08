#include <bits/stdc++.h>
#define maxn 2200
using namespace std;

typedef long long LL;

struct bit
{
	LL b[maxn][maxn];
	int nx, ny;
	void add(int x,int y,int z)
	{
		for (int i=x;i<=nx;i+=(i&-i))
			for (int j=y;j<=ny;j+=(j&-j))
				b[i][j]+=z;
	}
	LL ask(int x, int y)
	{
		LL tmp=0;
		for (int i=x;i;i-=(i&-i))
			for (int j=y;j;j-=(j&-j))
				tmp+=b[i][j];
		return tmp;
	}
	void init(int x, int y)
	{
		nx=x; ny=y;
		memset(b,0,sizeof(b));
	}
}s;
struct query
{
	int xo, yo, xe, ye;
	LL ans;
	query(){}
	query(int xo, int yo, int xe, int ye):
	xo(xo), yo(yo), xe(xe), ye(ye), ans(0){}
};
struct light
{
	int x, y, v;
	light(){}
	light(int x, int y, int v):
	x(x), y(y), v(v){}
};
vector<query> q;
vector<light> lt[maxn];
vector<int> askq[maxn];
int on[maxn];
int n,m,k,tot;

LL submatrix(int xo, int yo, int xe, int ye)
{
	return s.ask(xe,ye)-s.ask(xo-1, ye)-s.ask(xe, yo-1)+s.ask(xo-1, yo-1);
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	s.init(n+1,m+1);
	int x, y, z, tmp;
	for (int i=1;i<=k;i++)
	{
		scanf("%d",&tmp);
		for (int j=1;j<=tmp;j++)
		{
			scanf("%d%d%d",&x,&y,&z);
			lt[i].push_back(light(x,y,z));
		}
		on[i]=1;
	}
	scanf("%d",&tot);
	char sign[10];
	int xo,yo,xe,ye;
	for (int i=1;i<=tot;i++)
	{
		scanf(" %s",sign);
		if (sign[0]=='A')
		{
			scanf("%d%d%d%d",&xo,&yo,&xe,&ye);
			q.push_back(query(xo,yo,xe,ye));
			for (int j=1;j<=k;j++) if (on[j])
				askq[j].push_back(q.size()-1);
		}
		else
		{
			scanf("%d",&x);
			on[x]^=1;
		}
	}
	for (int i=1;i<=k;i++)
	{
		for (auto j:lt[i])
			s.add(j.x, j.y, j.v);
		for (auto j:askq[i])
			q[j].ans+=submatrix(q[j].xo, q[j].yo, q[j].xe, q[j].ye);
		for (auto j:lt[i])
			s.add(j.x, j.y, -j.v);
	}
	for (auto i:q) printf("%I64d\n",i.ans);
	return 0;
}