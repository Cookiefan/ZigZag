#include <bits/stdc++.h>
#define maxn 100200
using namespace std;

struct query
{
	int l, r, id;
	query(){}
	query(int l, int r, int id):l(l),r(r),id(id){}
}q[maxn];
bool operator <(query a, query b)
{
	return a.r<b.r;
}
int a[maxn], ans[maxn], lastpos[maxn*10];
int n, m;
map<int,int> s[maxn];

struct bit
{
	int sum[maxn];
	int num;
	bit(){ memset(sum,0,sizeof(sum)); }
	bit(int n):num(n){memset(sum,0,sizeof(sum)); }
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) sum[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i>=1;i-=(i&-i))  tmp+=sum[i];
		return tmp;
	}
	void clear()
	{
		memset(sum,0,sizeof(sum));
	}
};

int gcd(int a,int b)
{
    return (b==0?a:gcd(b, a%b));
}

int main()
{
	while (scanf("%d%d", &n,&m)!=EOF)
	{
		for (int i=0;i<=n;i++) s[i].clear();
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			for (auto p:s[i-1])
				s[i][gcd(p.first, a[i])]=p.second;
			s[i][a[i]]=i;
		}
		int x, y;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x, &y);
			q[i]=query(x, y, i);
		}
		sort(q+1, q+m+1);
		bit tree(n+10);
		q[0].r=0;
		memset(lastpos,-1,sizeof(lastpos));
		int j=1;
		for (int i=1;i<=m;i++)
		{
			while (j<=q[i].r)
			{
				for (auto p:s[j])
				{
					int x=p.first;
					if (lastpos[x]!=-1)
						tree.add(lastpos[x], -1);
					lastpos[x]=p.second;
					tree.add(lastpos[x], 1);
				}
				j++;
			}
			ans[q[i].id]=tree.ask(q[i].l);
		}
		for (int i=1;i<=m;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}