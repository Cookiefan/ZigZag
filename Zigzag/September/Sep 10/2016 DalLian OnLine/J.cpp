#include <bits/stdc++.h>
#define maxn 200200
using namespace std;

typedef long long LL;
vector<int> t[maxn];
int a[maxn], fa[maxn];
LL r[maxn];
int n, num;
LL m, ans, sum;

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

int getnum(LL x)
{
	int k=lower_bound(r+1, r+num+1, x)-r;
	if (r[k]>x) k--;
	return k;
}

void dfs(int x)
{
	//cout<<x<<' '<<s.ask(getnum(m/a[x]))<<endl;
	if (a[x]==0)
		ans+=sum;
	else
		ans+=s.ask(getnum(m/a[x]));
	//cout<<m/a[x]<<' '<<getnum(m/a[x])<<endl;
	s.add(getnum(a[x]), 1); sum++;
	for (int y:t[x])
		if (y!=fa[x])
			dfs(y);
	s.add(getnum(a[x]), -1); sum--;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%I64d",&n,&m);
		for (int i=1;i<=n;i++)
			t[i].clear();
		num=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			r[++num]=a[i];
		}
		r[++num]=0;
		r[++num]=1000000000000000001LL;
		sort(r+1, r+num+1);
		//for (int i=1;i<=num;i++) cout<<r[i]<<' '; cout<<endl;
		//for (int i=1;i<=n;i++) cout<<getnum(a[i])<<endl;
		int x, y;
		memset(fa,0,sizeof(fa));
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			fa[y]=x;
		}
		s.init(num+10);
		ans=0;
		for (int i=1;i<=n;i++)
			if (fa[i]==0)
			{
				sum=0;
				dfs(i);	
				break;
			}
		printf("%I64d\n",ans);
	}

	return 0;
}