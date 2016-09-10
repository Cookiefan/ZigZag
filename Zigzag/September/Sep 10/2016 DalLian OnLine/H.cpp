#include <bits/stdc++.h>
#define maxn 100200
#define inf 0x3f3f3f3f
using namespace std;

struct bit
{
	int b[120000];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]=min(b[i], z);
	}
	int ask(int x)
	{
		int tmp=inf;
		for (int i=x;i;i-=(i&-i)) tmp=min(tmp, b[i]);
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0x3f,sizeof(b));
	}
}s;
int n, m, num;
int a[maxn];
int r[maxn];
vector<int> t[maxn];

int get_num(int x)
{
	int k=lower_bound(r, r+num, x)-r;
	if (r[k]>x) k--;
	return k+1;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		num=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			r[num++]=a[i];
		}
		r[num++]=0;
		sort(r, r+num);
		s.init(100005);
		for (int i=n;i>=1;i--)
		{
			int tmp=i, x=a[i];
			while (tmp<=n && x!=0)
			{
				tmp=s.ask(get_num(x));
				if (tmp<=n)
				{
					t[i].push_back(tmp);
					x=x%a[tmp];
				}
			}
			s.add(get_num(a[i]), i);
		}
		scanf("%d",&m);
		int x, y;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			int ans=a[x];
			for (int e:t[x])
			{
				if (e>y) break;
				ans%=a[e];
			}
			printf("%d\n",ans);
		}
		for (int i=1;i<=n;i++)
			t[i].clear();
	}
	return 0;
}