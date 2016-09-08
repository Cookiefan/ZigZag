#include <bits/stdc++.h>
#define maxn 502000
using namespace std;
int p[maxn],e[maxn];
long long s[maxn],sb[maxn];
int n;
char c;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d ",&p[i]);
	for (int i=1;i<=n;i++)
	{
		scanf(" %c",&c);
		if (c=='B') e[i]=1;
		else e[i]=0;
	}
	long long ans=0;
	memset(s,0,sizeof(s));
	memset(sb,0,sizeof(sb));
	for (int i=1;i<=n;i++)
	{
		s[i]=s[i-1]+p[i];
		if (e[i]) sb[i]=sb[i-1]+p[i];
		else sb[i]=sb[i-1];
	}
	for (int i=0;i<=n;i++) ans=max(ans,sb[n]-sb[i]+s[i]-sb[i]);
	memset(s,0,sizeof(s));
	memset(sb,0,sizeof(sb));
	for (int i=n;i>=1;i--)
	{
		s[i]=s[i+1]+p[i];
		if (e[i]) sb[i]=sb[i+1]+p[i];
		else sb[i]=sb[i+1];
	}
	for (int i=n+1;i>=1;i--) ans=max(ans,sb[1]-sb[i]+s[i]-sb[i]);
	printf("%I64d\n",ans);
	
	return 0;
}