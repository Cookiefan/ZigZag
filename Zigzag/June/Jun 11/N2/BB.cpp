#include <bits/stdc++.h>
#define maxn 1200
#define inf 99999999
#define pii pair<int,int>
using namespace std;

deque<int> a[maxn];
int w[maxn], s[maxn];
pii task[maxn];
int n,p, mx;

bool judge(int d)
{
	//cout<<d<<":  \n";
	for (int i=1;i<=n;i++)
	{
		w[i]=0;
		for (int j=0;j<s[i];j++)
			w[i]=max(w[i], a[i][j]-d-j);
		task[i]=pii(w[i], s[i]);
	}
	sort(task+1, task+n+1);
	//for (int i=1;i<=n;i++) cout<<task[i].first<<','<<task[i].second<<' '; cout<<endl;
	int now=0, i=1;
	while (now>=task[i].first && i<=n)
	{
		now+=task[i].second;
		i++;
	}
	// cout<<i<<endl;
	return (i==n+1);
}

int main()
{
	int x, sx, y, sy;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		for (int j=1;j<=s[i];j++)
		{
			scanf("%d",&x);
			mx=max(mx, x);
			a[i].push_back(x);
		}
	}
	scanf("%d",&p);
	for (int i=1;i<=p;i++)
	{
		scanf("%d%d%d%d",&x,&sx,&y,&sy);
		stack<int>tmpx, tmpy;
		for (int i=1;i<=sx;i++)
		{
			tmpx.push(a[x].front());
			a[x].pop_front();
		}
		for (int i=1;i<=sy;i++)
		{
			tmpy.push(a[y].front());
			a[y].pop_front();
		}
		for (int i=1;i<=sy;i++)
		{
			a[x].push_front(tmpy.top());
			tmpy.pop();
		}
		for (int i=1;i<=sx;i++)
		{
			a[y].push_front(tmpx.top());
			tmpx.pop();
		}
		s[x]=a[x].size();
		s[y]=a[y].size();
		// for (int i=1;i<=n;i++)
		// {
		// 	for (int j=0;j<s[i];j++)
		// 		cout<<a[i][j]<<' ';
		// 	cout<<endl;
		// }
		int l=0, r=mx+1, ans=0;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (judge(mid))
			{
				ans=mid;
				r=mid-1;
			}
			else
				l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}