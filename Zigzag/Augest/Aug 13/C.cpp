#include <bits/stdc++.h>
#define maxn 2200
using namespace std;

typedef long long LL;
const LL oo=1000000007;
struct bit
{
	LL b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) (b[i]+=z)%=oo;
	}
	LL ask(int x)
	{
		LL tmp=0;
		for (int i=x;i;i-=(i&-i)) (tmp+=b[i])%=oo;
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}s;

LL f[maxn];
int a[maxn], b[maxn];
int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]), b[i]=a[i];
		sort(b+1, b+n+1);
		for (int i=1;i<=n;i++) a[i]=lower_bound(b+1, b+n+1, a[i])-b;
		//for (int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
		for (int i=1;i<=n;i++) f[i]=1;
		for (int k=1;k<=m-1;k++)
		{
			s.init(n+10);
			for (int i=1;i<=n;i++)
			{
				s.add(a[i], f[i]);
				f[i]=s.ask(a[i]-1);
			}
		}
		LL ans=0;
		for (int i=1;i<=n;i++) (ans+=f[i])%=oo;
		printf("Case #%d: %I64d\n",o,ans);
	}
	return 0;
}