#include <bits/stdc++.h>
#define maxn 52000
#define square(x) ((x) * (x))
using namespace std;

int idx;
struct Node
{
	int x[12];
	Node *lc, *rc;
	node(){}
	bool operator < (const Node &u) const
	{
		return x[idx]<u.x[idx];
	}
}data[maxn];
typedef pair<double, Node*> pdn;
struct kdt
{
	Node *rot;
	int k;
	priority_queue<pdn>que;
	kdt(){}
	kdt(int k):k(k){rot=NULL;}
	Node* build(int l, int r, int dep)
	{
		if (l>r) return NULL;
		Node *now=new Node();
		idx=dep%k;
		int mid=(l+r)>>1;
		nth_element(data+l, data+mid, data+r+1);
		memcpy(now->x, data[mid].x, sizeof(now->x));
		//for (int i=0;i<k;i++) cout<<now->x[i]<<' '; cout<<endl;
		now->lc=build(l, mid-1, dep+1);
		now->rc=build(mid+1, r, dep+1);
		return now;
	}
	void build(int n, int nk)
	{
		k=nk;
		rot=build(0, n-1, 0);
	}
	void query(Node* now, Node *p, int m, int dep)
	{
		if (now==NULL) return ;
		double sum=0;
		for (int i=0;i<k;i++)
			sum+=square(now->x[i]-p->x[i]);
		int dim=dep%k;
		Node *ll=now->lc, *rr=now->rc;
		if (p->x[dim]>=now->x[dim]) swap(ll, rr);
		query(ll, p, m, dep+1);
		if (que.size()<m)
		{
			que.push(pdn(sum, now));
			query(rr, p, m, dep+1);
		}
		else
		{
			if (sum<que.top().first)
			{
				que.pop();
				que.push(pdn(sum, now));
			}
			if (square(p->x[dim]-now->x[dim])<que.top().first)
				query(rr, p, m, dep+1);
		}
	}
	void query(Node *p, int m)
	{
		while (!que.empty()) que.pop();
		query(rot, p, m, 0);
	}
	void print()
	{
		vector<Node*> t;
		t.clear();
		while (!que.empty())
		{
			t.push_back(que.top().second);
			que.pop();
		}
		int num=t.size();
		for (int i=num-1;i>=0;i--)
			for (int j=0;j<k;j++)
				printf(j==k-1?"%d\n":"%d ",t[i]->x[j]);
	}
}s;
int n,k,m,q;

int main()
{
	while (scanf("%d%d",&n,&k)!=EOF)
	{
		for (int i=0;i<n;i++)
			for (int j=0;j<k;j++)
				scanf("%d",&data[i].x[j]);
		s.build(n, k);
		scanf("%d",&q);
		for (int i=1;i<=q;i++)
		{
			Node *p=new Node();
			for (int j=0;j<k;j++)
				scanf("%d",&p->x[j]);
			scanf("%d",&m);
			s.query(p, m);
			printf("the closest %d points are:\n",m);
			s.print();
			delete p;
		}
	}
	return 0;
}