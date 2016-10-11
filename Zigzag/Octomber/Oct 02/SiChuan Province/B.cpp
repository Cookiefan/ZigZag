#include <bits/stdc++.h>
#define oo 1000000007
#define maxn 200200
using namespace std;

typedef long long LL;
LL s[1<<20], sum, sum2, cnt;
int n,m,msk;

int main()
{	
	cout<<(int)' '<<endl;
	//cout<<exp(2, 4, 10000)<<endl;
	scanf("%d%d",&n,&m);
	int x,y,z;
	sum=0;
	for (int i=1;i<=m;i++)
	{
		msk=0;
		scanf("%d%d",&y,&x);
		for (int i=1;i<=x;i++)
		{
			scanf("%d",&z); z--;
			msk=msk|(1<<z);
		}
		(s[msk]+=y)%=oo;
		(sum+=y)%=oo;
	}
	LL ans=0;
	for (int i=0;i<(1<<n);i++)
		if (s[i])
		{
			(ans+=s[i]*(sum-s[i]+oo)%oo*((LL)1<<(n-2))%oo)%=oo;
			(ans+=s[i]*s[i]%oo*((LL)1<<(n-1)))%=oo;
		}
	printf("%lld\n", ans);
	return 0;
}