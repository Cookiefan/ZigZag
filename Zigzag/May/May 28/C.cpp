#include <bits/stdc++.h>
#define inf 99999999
#define maxn 120000
using namespace std;

int sum[maxn];

int change(string s, int st, int l, int r)
{
	int n=s.length()-1, tmp1=0, tmp2=0;
	sum[0]=0;
	for (int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]!=s[n+1-i]);

	string t=s;
	int now=st, lm=sum[st]-sum[l-1], rm=sum[r]-sum[st];
	while (lm+rm>0)
	{
		if (t[now]!=t[n+1-now])
		{
			tmp1+=min(abs(t[now]-t[n+1-now]), 26-abs(t[now]-t[n+1-now]));
			t[now]=t[n+1-now];
			if (lm>0) lm--;
			else rm--;
		}
		if (lm) tmp1++, now--;
		else if (rm) tmp1++, now++;
	}
	t=s;
	now=st, rm=sum[r]-sum[st-1], lm=sum[st-1]-sum[l-1];
	while (lm+rm>0)
	{
		if (t[now]!=t[n+1-now])
		{
			tmp2+=min(abs(t[now]-t[n+1-now]), 26-abs(t[now]-t[n+1-now]));
			t[now]=t[n+1-now];
			if (rm>0) rm--;
			else lm--;
		}
		if (rm) tmp2++, now++;
		else if (lm) tmp2++, now--;
	}
	return min(tmp1, tmp2);
}

int n, st;
string s;
int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&st);
		int l, r;
		if (n%2==1 && st==n/2+1) l=1, r=n;
		else if (st<=n/2) l=1, r=n/2;
		else l=n/2+1+n%2, r=n;
		cin>>s;
		int ans=change(" "+s, st, l, r);
		printf("%d\n",ans);
	}
	return 0;
}