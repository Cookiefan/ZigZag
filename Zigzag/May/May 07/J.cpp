#include <bits/stdc++.h>
#define maxn 520000
using namespace std;

struct seg
{
	int l, r;
	seg(){}
	seg(int l, int r):l(l),r(r){}
	friend bool operator ==(seg a, seg b){ return a.l==b.l && a.r==b.r; }
	friend bool operator < (seg a, seg b){ return a.r<b.r; }
};
set<seg> s;
typedef set<seg>::iterator sit;

int n;

int main()
{
	scanf("%d",&n);
	int x, p;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if (x>0)
		{
			scanf("%d",&p);
			int st,ed;
			sit now=s.lower_bound(seg(x,x));
			sit pre=now
			if (now==s.end())
			{
				st=x; ed=x+p-1;
				if (now==s.begin())
					s.insert(seg(st,ed));
				else
				{
					sit tmp=now; tmp--;
					if (tmp!=s.end() && tmp->r==x-1)
					{
						s.erase(tmp);
						s.insert(seg(tmp->l, ed));
					}
					else
						s.insert(seg(x, ed));
				}
			}
			else if (x<now->l)
			{
				st=x;
				if (x+p-1<=now->l-1)
				{
					ed=x+p-1;
					s.insert(seg(x, ed));
				}
				else
				{
					ed=now->l-1;
					s.erase(now);
					s.insert(seg(x, now->r));
				}
			}
			else
			{
				st=now->r+1;
				sit tmp=now; tmp++;
				if (tmp!=s.end() && st+p-1>=tmp->l)
				{
					ed=tmp->l-1;
					s.erase(now);
					s.erase(tmp);
					s.insert(seg(now->l, tmp->r));
				}
				else
				{
					ed=st+p-1;
					s.erase(now);
					s.insert(seg(now->l, ed));
				}
			}
			printf("%d %d\n",st, ed);
		}
		else
		{
			x=x*(-1);
			sit now=s.lower_bound(seg(x, x));
			if (now!=s.end() && now->l<=x)
			{
				if (now->l>now->r) s.erase(now);
				if (now->l<x) s.insert(seg(now->l, x-1));
				if (now->r>x) s.insert(seg(x+1, now->r));				
			}
		}
		for (sit k=s.begin();k!=s.end();k++)
			cout<<'['<<k->l<<','<<k->r<<']'<<' ';
		cout<<endl;
	}
	return 0;
}