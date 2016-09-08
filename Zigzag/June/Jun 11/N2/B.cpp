#include <bits/stdc++.h>
#define maxn 1200
using namespace std;

deque<int> a[maxn];
int q[maxn], s[maxn];
int n,p, mx;

bool judge(int d)
{
	//cout<<d<<endl;
	for (int i=1;i<=n;i++) q[i]=i;
	do
	{
		int now=d, flag=1;
		//for (int k=1;k<=n;k++) cout<<q[k]<<' ';cout<<endl;
		for (int i=1;i<=n;i++)
		{
			
			int k=q[i];
			for (int j=0;j<s[k];j++)
			{
				//cout<<now<<','<<a[k][j]<<' ';
				if (now<a[k][j])
				{
					//cout<<now<<' '<<a[k][j]<<endl;
					flag=0;
					break;
				}
				else now++;
			}
			
		}
		if (flag) return 1;
		//cout<<endl;
	}while (next_permutation(q+1, q+n+1));
	return 0;
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