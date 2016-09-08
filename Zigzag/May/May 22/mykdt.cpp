#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define maxn 12
#define lson now<<1
#define rson now<<1 |1
#define Sqrt2(x) (x) * (x)
#define Pair pair<double , Node>
using namespace std;

int n, k, idx;
struct Node
{
	int x[8000];
	int id;
	bool operator < (const Node &u) const
	{
		return x[idx]<u.x[idx];
	}
}_data[maxn];

priority_queue<Pair> q;

class KDTree
{
public:
	void Build(int ,int, int , int);
	void Query(int ,Node, int, int);
private:
	Node data[4*maxn];
	int flag[4*maxn];
}KDT;

void KDTree::Build(int now, int l, int r, int dep)
{
	if (l > r) return ;
	flag[now]=1;
	flag[now<<1]=flag[now<<1 | 1]=-1;
	idx=dep%k;
	int mid=(l+r)>>1;
	nth_element(_data+l, _data+mid, _data+r+1);
	data[now]=_data[mid];
	for (int i=0;i<k;i++) cout<<data[now].x[i]<<' '; cout<<endl;
	Build(lson, l, mid-1, dep+1);
	Build(rson, mid+1, r, dep+1);
}
void KDTree::Query(int now, Node p, int m, int dep)
{
	if (flag[now]==-1) return ;
	Pair tmp(0, data[now]);
	for (int i=0;i<k;i++)
		tmp.first+=Sqrt2(tmp.second.x[i]-p.x[i]);
	int dim=dep%k;
	bool fg=0;
	int ls=lson, rs=rson;
	if (p.x[dim]>=data[now].x[dim]) swap(ls,rs);
	if (~flag[ls]) Query(ls, p, m, dep+1);
	if (q.size()<m)
	{
		q.push(tmp);
		fg=1;
	}
	else
	{
		if (tmp.first < q.top().first)
		{
			q.pop();
			q.push(tmp);
		}
		if (Sqrt2(p.x[dim]-data[now].x[dim])<q.top().first)
		{
			fg=1;
		}
	}
	if (~flag[rs] && fg) Query(rs, p, m, dep+1);
}

void Print(Node now)
{
	cout<<now.id<<endl;
	// for (int i=0;i<k;i++)
	// 	printf(i==k-1?"%d\n":"%d ", now.x[i]);
}

int main()
{
	freopen("color.txt","r",stdin);
	while (scanf("%d%d",&n, &k)!=EOF)
	{
		cout<<n<<k<<endl;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<k;j++)
			{
				scanf("%d", &_data[i].x[j]);
			}
			_data[i].id=i;
		}
		KDT.Build(1, 0, n-1, 0);
		int t,m;
		scanf("%d",&t);
		while (t--)
		{
			Node p;
			for (int i=0;i<k;i++)
				scanf("%d",&p.x[i]);
			scanf("%d",&m);
			while (!q.empty()) q.pop();
			KDT.Query(1, p, m, 0);
			printf("the closest %d points are:\n", m);
			Node tmp[26];
			for (int i=0; !q.empty(); i++)
			{
				tmp[i]=q.top().second;
				q.pop();
			}
			for (int i=m-1; i>=0; i--) Print(tmp[i]);
		}
	}
	return 0;
}