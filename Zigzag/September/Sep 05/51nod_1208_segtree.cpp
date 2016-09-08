#include <bits/stdc++.h>
#define maxn 220000
using namespace std;
struct query
{
	int x, yo, ye, z;
	query(){}
	query(int x, int yo, int ye, int z):
	x(x), yo(yo), ye(ye), z(z){}
};
bool operator <(query a, query b)
{
	return a.x<b.x;
}
vector<query> q;
int ax[maxn], ay[maxn];
int nx, ny, n;
int H, W;

int mx[maxn*6], add[maxn*6];
void update(int x)
{
	mx[x]=max(mx[x<<1], mx[x<<1|1]);
}

void addvalue(int x, int z)
{
	mx[x]+=z;
	add[x]+=z;
}

void down(int x)
{
	if (!add[x]) return;
	addvalue(x<<1, add[x]);
	addvalue(x<<1|1, add[x]);
	add[x]=0;
}

void change(int x, int l, int r, int ll, int rr, int z)
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

int main()
{
	scanf("%d%d%d",&n,&W,&H);
	nx=ny=0;
	q.clear();
	int x, y, z;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		q.push_back(query(x, y, y+H, z));
		q.push_back(query(x+W+1, y, y+H, -z));
		ax[nx++]=x;
		ax[nx++]=x+W+1;
		ay[ny++]=y;
		ay[ny++]=y+H;
	}
	sort(ax, ax+nx);
	nx=unique(ax, ax+nx)-ax;
	sort(ay, ay+ny);
	ny=unique(ay, ay+ny)-ay;

	sort(q.begin(), q.end());
	int ss=q.size();
	for (int i=0;i<ss;i++)
	{
		q[i].x=lower_bound(ax, ax+nx, q[i].x)-ax;
		q[i].yo=lower_bound(ay, ay+ny, q[i].yo)-ay;
		q[i].ye=lower_bound(ay, ay+ny, q[i].ye)-ay;
	}
	memset(add,0,sizeof(add));
	memset(mx, 0, sizeof(mx));
	int ans=0;
	for (int i=0;i<ss;i++)
	{
		change(1, 0, ny, q[i].yo, q[i].ye, q[i].z);
		if (i<ss-1 && q[i].x==q[i+1].x) continue;
		ans=max(ans, mx[1]);
	}
	printf("%d\n",ans);


	return 0;
}