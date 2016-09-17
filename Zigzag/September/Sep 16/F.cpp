#include <bits/stdc++.h>
#define maxn 1000200
using namespace std;
typedef long long LL;
const LL oo=1e9+7;
//快速幂
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

int n,m;
LL s[maxn];
LL f[maxn], g[maxn];

int main()
{
	s[0]=0;
	for (int i=1;i<=1000000;i++) s[i]=s[i-1]+i;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		if (m==1){
			printf("Case #%d: %d\n",o, 0);
			continue;
		}
		int l=-1, r=-1;
		for (int j=m-1;j>=0;j--)
			if (s[j]<s[m]-s[j])
			{
				l=j+1;
				break;
			}
		f[m-1]=g[m-1]=0;
		f[m]=g[m]=1;
		for (int i=m+1;i<=n;i++)
		{
			f[i]=g[i]=0;
			int l=m, r=i-1, j;
			while (l<=r)
			{
				int mid=(l+r)>>1;
				if (s[i]-s[mid]<=s[mid])
				{
					j=mid;
					r=mid-1;
				}
				else
					l=mid+1;
			}
			f[i]=((f[i]+g[i-1])%oo-g[j-1]+oo)%oo;
			g[i]=(g[i-1]+f[i])%oo;
			//cout<<i<<' '<<f[i]<<endl;
		}
		// for (int j=m;j<=n;j++)
		// 	if (s[j]>=s[n]-s[j])
		// 	{
		// 		r=j;
		// 		break;
		// 	}
		LL ans=exp(2, l-1, oo)*f[n]%oo*2%oo;
		if (l==1) ans=ans*2%oo;
		//cout<<l<<' '<<r<<endl;
		printf("Case #%d: %d\n",o, ans);
	}
	return 0;
}