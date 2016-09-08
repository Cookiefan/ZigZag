#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
int ans[maxn], a[maxn];
int n;

struct bit
{
	int b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}s;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		s.init(n);
		for (int i=n;i>=1;i--)
		{
			int r=i+s.ask(a[i]-1), l=min(a[i], i);
			ans[a[i]]=r-l;
			s.add(a[i], 1);
		}
		printf("Case #%d: ",o);
		for (int i=1;i<=n;i++)
			printf(i<n?"%d ":"%d\n",ans[i]);
	}
	return 0;
}