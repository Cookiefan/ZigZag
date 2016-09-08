#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define pis pair<int, seg>
#define maxn 22000
#define inf 999999999
using namespace std;

struct bit
{
	int s[4200000];
	int num;
	void add(int x, int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) s[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=s[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(s,0,sizeof(s));
	}
}tree;

struct seg
{
	int l, r;
	seg(){}
	seg(int l, int r):l(l),r(r){}
	friend bool operator <(seg a, seg b)
	{
		return a.l==b.l ?  a.r>b.r : a.l<b.l;
	};
}s[maxn];
priority_queue<pis> que;
vector<seg> sll, srr;
vector<pis> pll, prr;
int n, nl, nr;
const int high=10000;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int x, y, z, d;
		nl=nr=0;
		sll.clear(); srr.clear();
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&x,&y,&z,&d);
			x+=2000000; y+=2000000;
			int delta=high-z;
			if (d<0) nl++, sll.push_back(seg(x-delta, y+delta));
			else nr++, srr.push_back(seg(x-delta, y+delta));
		}
		sort(sll.begin(), sll.end());
		sort(srr.begin(), srr.end());
		// cout<<"sll:\n";
		// for (int i=0;i<nl;i++) cout<<sll[i].l<<' '<<sll[i].r<<endl;
		// cout<<"srr:\n";
		// for (int i=0;i<nr;i++) cout<<srr[i].l<<' '<<srr[i].r<<endl;
		int j=0;
		pll.clear();
		tree.init(4000000);
		for (int i=0;i<nl;i++) tree.add(sll[i].r, 1);
		for (int i=0;i<nl;i++)
		{
			int tmp=tree.ask(sll[i].l+2*high);
			// cout<<tmp<<endl;
			pll.push_back(pis(tmp, sll[i]));
			tree.add(sll[i].r, -1);
		}
		j=0;
		prr.clear();
		tree.init(4000000);
		for (int i=0;i<nr;i++) tree.add(srr[i].r, 1);
		for (int i=0;i<nr;i++)
		{
			int tmp=tree.ask(srr[i].l+2*high);
			//cout<<tmp<<endl;
			prr.push_back(pis(tmp, srr[i]));
			tree.add(srr[i].r, -1);
		}
		int ans=0;
		while (!que.empty()) que.pop();
		for (int i=0;i<nl;i++) que.push(pll[i]);
		if (!que.empty()) ans=max(ans, que.top().first);
		for (int j=0;j<nr;j++)
		{
			int tmp=prr[j].first;
			while (!que.empty() && que.top().second.l<prr[j].second.l) que.pop();
			//cout<<que.top().second.l<<' '<<que.top().second.r<<endl;
			if (!que.empty()) tmp+=que.top().first;
			ans=max(ans, tmp);
		}
		printf("Case #%d:\n%d\n", o, ans);
	}
	return 0;
}