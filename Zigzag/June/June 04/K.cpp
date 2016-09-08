#include <bits/stdc++.h>
#define maxn 120
using namespace std;

int lc[maxn], rc[maxn];
int po[maxn], mo[maxn];
int n, rot;
int build(int k, int st, int ed)
{
	if (st>ed) return 0;
	for (int i=1;i<=n;i++)
		if (po[k]==mo[i])
		{
			lc[po[k]]=build(k+1, st, i-1);
			rc[po[k]]=build(k+i-st+1, i+1, ed);
		}
	return po[k];
}

void reverse(int x)
{
	if (lc[x]) reverse(lc[x]);
	if (rc[x]) reverse(rc[x]);
	swap(lc[x],rc[x]);
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&mo[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&po[i]);
	rot=build(1, 1, n);
	reverse(rot);
	deque<int> que;
	vector<int> l;
	que.clear();
	que.push_back(rot);
	while (!que.empty())
	{
		int x=que.front();
		que.pop_front();
		l.push_back(x);
		if (lc[x]) que.push_back(lc[x]);
		if (rc[x]) que.push_back(rc[x]);
	}
	int num=l.size();
	for (int i=0;i<num;i++)
		printf(i==num-1?"%d\n":"%d ",l[i]);
	return 0;
}