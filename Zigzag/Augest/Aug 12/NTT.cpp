#include <bits/stdc++.h>
#define maxn 202000
#define mod 998244353
#define G 3
using namespace std;
typedef long long LL;
const double pi=acos(-1.0);
int n,m,num;
LL a[maxn], b[maxn], ans[maxn];
string s, t;

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

int rev(int x, int n)
{
	int tmp=0;
	for (int i=1;i<n;i<<=1)
	{
		tmp<<=1;
		if (x & i) tmp |=1;
	}
	return tmp;
}

void ntt(LL *a, int n, int flag)
{
	for (int i=0;i<n;i++)
		if (i<rev(i, n))
			swap(a[rev(i, n)], a[i]);
	for (int i=1;i<n;i<<=1)
	{	
		LL wn=exp(G, (mod-1)/(i<<1), mod);
		if (flag==-1) wn=exp(wn, mod-2, mod);
		for (int j=0;j<n;j+=(i<<1))
		{
			LL w=1;
			for (int k=0;k<i;k++, w=w*wn%mod)
			{
				LL x=a[j+k], y=w*a[j+k+i]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+i]=(x-y+mod)%mod;
			}
		}

	}
	if (flag==-1)
	{
		int inv=exp(n, mod-2, mod);
		for (int i=0;i<n;i++) a[i]=a[i]*inv%mod;
	}
}


int main()
{
	while (cin>>s)
	{
		memset(ans,0,sizeof(ans));
		n=s.length();
		cin>>t;
		m=t.length();
		int num=1;
		while (num<max(n,m)) num<<=1;
		num<<=1;
		for (int i=0;i<num;i++)
		{
			a[i]=i<n?s[n-i-1]-'0':0;
			b[i]=i<m?t[m-i-1]-'0':0;
		}
		ntt(a, num, 1);
		ntt(b, num, 1);
		for (int i=0;i<num;i++) ans[i]=a[i]*b[i]%mod;
		ntt(ans, num, -1);
		for (int i=0;i<num;i++)
		{
			ans[i+1]+=ans[i]/10;
			ans[i]%=10;
		}
		while (ans[num]>0) num++;
		while (ans[num-1]==0 && num>1) num--;
		for (int i=num-1;i>=0;i--) printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}