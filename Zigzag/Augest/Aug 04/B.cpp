#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pll;

LL frac[220000];
const LL oo=110119;

LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

LL com(LL n,LL m,LL p)
{
	if (m>n) return 0;
	LL ans=frac[n]*exp(frac[m], p-2, p)%p*exp(frac[n-m], p-2, p)%p;
	return ans;
}

LL lucas(LL n,LL m,LL p)
{
	if (m==0) return 1;
	return com(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}

LL get_ans(LL dx, LL dy)
{
	if (!(dx>=0 && dy>=0 && dx*2>=dy && (dx*2-dy)%3==0 && dy*2>=dx && (dy*2-dx)%3==0))
		return 0;
	LL x=(dx*2-dy)/3;
	LL y=(dy*2-dx)/3;
	return lucas(x+y, y, oo);
}

LL f[maxn];
LL x,y;
vector<pll> q;
int p;
LL n,m;

int main()
{
	int o=0;
	frac[0]=1;
	for (int i=1;i<=150000;i++) frac[i]=frac[i-1]*i%oo;
	while (scanf("%I64d%I64d%d",&n,&m,&p)!=EOF)
	{
		memset(f,0,sizeof(f));
		q.clear();
		q.push_back(pll(1,1));
		for (int i=1;i<=p;i++)
		{
			scanf("%I64d%I64d",&x,&y);
			q.push_back(pll(x,y));
		}
		q.push_back(pll(n,m));
		sort(q.begin(), q.end());
		for (int i=1;i<=p+1;i++)
		{
			f[i]=get_ans(q[i].first-1, q[i].second-1);
			for (int j=1;j<i;j++)
				f[i]=(f[i]-f[j]*get_ans(q[i].first-q[j].first, q[i].second-q[j].second)%oo+oo)%oo;
		}
		printf("Case #%d: %I64d\n",++o,f[p+1]);
	}
	return 0;
}