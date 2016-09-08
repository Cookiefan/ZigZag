#include <bits/stdc++.h>
#define maxn 500020
#define inf 999999999
#define X first
#define Y second
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
struct query
{
	int x, yo, ye, z;
	query(){}
	query(int x, int yo, int ye, int z):
	x(x), yo(yo), ye(ye), z(z){}
	friend bool operator <(query a, query b)
	{
		return a.x<b.x;
	};
};
vector<query> q;
pii p[maxn];
int ax[maxn], ay[maxn];
LL mx[maxn*6], add[maxn*6];
int n, nx, ny, W, H, num;
LL ans, ff;

void update(int x)
{
	mx[x]=max(mx[x<<1], mx[x<<1|1]);
}

void addvalue(int x, LL z)
{
	mx[x]+=z;
	add[x]+=z;
}

void down(int x)
{
	if (add[x])
	{
		addvalue(x<<1, add[x]);
		addvalue(x<<1|1, add[x]);
		add[x]=0;
	}
}

void change(int x, int l, int r, int ll, int rr, LL z)
{
	if (ll<=l && r<=rr)
	{
		addvalue(x, z);
		return ;
	}
	down(x);
	int mid=(l+r)>>1;
	if (ll<=mid) change(x<<1, l, mid, ll, rr, z);
	if (rr>mid) change(x<<1|1, mid+1, r, ll, rr, z);
	update(x);
}

int getX(int x)
{
	return lower_bound(ax, ax+nx, x)-ax;
}

int getY(int y)
{
	return lower_bound(ay, ay+ny, y)-ay;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&W,&H);
		nx=ny=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&p[i].X, &p[i].Y);
			ax[nx++]=p[i].X;
			ax[nx++]=p[i].X+W;
			ay[ny++]=p[i].Y;
			ay[ny++]=p[i].Y+H-1;
		}
		ax[nx++]=inf;
		ax[nx++]=-inf;
		ay[ny++]=inf;
		ay[ny++]=-inf;

		sort(ax, ax+nx);
		nx=unique(ax, ax+nx)-ax;
		sort(ay, ay+ny);
		ny=unique(ay, ay+ny)-ay;
		q.clear();
		ff=n+1;
		for (int i=1;i<=n;i++)
		{
			q.push_back(query(getX(-inf), getY(p[i].Y), getY(p[i].Y+H-1), 1));
			q.push_back(query(getX(inf), getY(p[i].Y), getY(p[i].Y+H-1), -1));
			q.push_back(query(getX(p[i].X), getY(-inf), getY(inf), 1));
			q.push_back(query(getX(p[i].X+W), getY(-inf), getY(inf), -1));
			q.push_back(query(getX(p[i].X), getY(p[i].Y), getY(p[i].Y+H-1), -ff));
			q.push_back(query(getX(p[i].X+W), getY(p[i].Y), getY(p[i].Y+H-1), ff));
		}
		// for (int i=0;i<q.size();i++)
		// 	cout<<"x: "<<q[i].x<<" y: "<<q[i].yo<<' '<<q[i].ye<<" z: "<<q[i].z<<endl;
		sort(q.begin(), q.end());
		memset(mx,0,sizeof(mx));
		memset(add,0,sizeof(add));
		int ss=q.size();

		LL ans=0;
		for (int i=0;i<ss;i++)
		{
			change(1, 0, ny, q[i].yo, q[i].ye, q[i].z);
			if (i<ss-1 && q[i].x==q[i+1].x) continue;
			ans=max(ans, mx[1]);
		}
		printf("Case #%d: %lld\n",o, ans);
	}
	return 0;
}