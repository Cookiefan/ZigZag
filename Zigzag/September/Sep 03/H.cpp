#include <bits/stdc++.h>
#define maxn 100200
#define sqr(p) ((p)*(p))
using namespace std;

const int oo=1e9+7;
typedef long long LL;
LL p[maxn], q[maxn], r[maxn], d[maxn], t[maxn], f[maxn];
int n;

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		char c;
		for (int i=1;i<=n;i++)
		{
			scanf(" %c",&c);
			d[i]=c-'0';
			r[i]=(r[i-1]+d[i])%oo;
			p[i]=(p[i-1]+i*d[i])%oo;
			q[i]=(q[i-1]+(n-i+1)*d[i])%oo;
		}
		t[n]=1;
		for (int i=n-1;i>=1;i--) t[i]=(t[i+1]*10)%oo;
		LL ans=0;
		for (int i=1;i<=n;i++)
		{
			f[i]=t[i]*d[i]%oo*(((LL)i*(i-1)/2+(LL)(n-i+1)*(n-i)/2+min(i, n-i+1))%oo)%oo;
			if (i<=n/2) f[i]+=t[i]*((p[i-1]+(LL)i*(r[n-i+1]-r[i]+oo)%oo+(q[n]-q[n-i+1]+oo)%oo)%oo)%oo;
			else f[i]+=t[i]*((p[n-i+1]+(LL)(n-i+1)*(r[i-1]-r[n-i+1]+oo)%oo+(q[n]-q[i]))%oo)%oo;
			ans=(ans+f[i])%oo;
			//cout<<i<<":  "<<f[i]<<endl;
		}
		printf("%d\n",ans);
	}

	return 0;
}