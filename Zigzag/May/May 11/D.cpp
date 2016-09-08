#include <bits/stdc++.h>
#define maxn 220000
#define maxm 12000
using namespace std;

struct query
{
	int tp, x, id, h;
	friend bool operator <(query a, query b)
	{
		return a.h==b.h?a.id<b.id:a.h<b.h;
	}
}q[maxn], nq[maxn];
int ans[maxn];

int n;

void solve(int l, int r)
{
	if (l==r)
		return ;
	int mid=(l+r)>>1;
	solve(l, mid);
	solve(mid+1, r);
	
	int i=l, j=mid+1, k=0;
	map<int, int> s; s.clear();
	while (i<=mid || j<=r)
	{
		if ((j>r) || (i<=mid && q[i].h<=q[j].h))
		{
			if (q[i].tp==1)
			{
				if (s.find(q[i].x)==s.end()) s[q[i].x]=0;
				s[q[i].x]++;
			}
			else if (q[i].tp==2)
			{
				if (s.find(q[i].x)==s.end()) s[q[i].x]=0;
				s[q[i].x]--;
			}
			nq[k++]=q[i++];
			continue;
		}
		if ((i>mid) || (j<=r && q[j].h<q[i].h))
		{
			if (q[j].tp==3 && s.find(q[j].x)!=s.end())
				ans[q[j].id]+=s[q[j].x];
			nq[k++]=q[j++];
			continue;
		}
	}
	for (int i=0;i<k;i++) q[l+i]=nq[i];
	// cout<<l<<' '<<r<<": "<<endl;
	// for (int i=l;i<=r;i++)
	// 	cout<<q[i].h<<' '<<q[i].tp<<' '<<q[i].x<<endl;
}

int main()
{
	scanf("%d",&n);
	memset(ans,-1,sizeof(ans));
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&q[i].tp, &q[i].h, &q[i].x);
		if (q[i].tp==3) ans[i]=0;
		q[i].id=i;
	}

	solve(1, n);

	for (int i=1;i<=n;i++)
		if (ans[i]!=-1)
			printf("%d\n",ans[i]);

	return 0;
}