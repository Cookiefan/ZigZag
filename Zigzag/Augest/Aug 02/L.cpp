#include <bits/stdc++.h>
#define maxn 80000
using namespace std;

struct prefix_bit
{
	long long b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	long long ask(int x)
	{
		long long tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void clear()
	{
		memset(b,0,sizeof(b));
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}dw;

struct suffix_bit
{
	long long b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i;i-=(i&-i)) b[i]+=z;
	}
	long long ask(int x)
	{
		long long tmp=0;
		for (int i=x;i<=num;i+=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void clear()
	{
		memset(b,0,sizeof(b));
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}up;

int a[maxn],c[maxn];
long long lu[maxn], ld[maxn], ru[maxn], rd[maxn];
int n;
long long s1,s2,t1,t2,t3,t4,ans;

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		memcpy(c,a,sizeof(a));
		sort(c+1, c+n+1);
		for (int i=1;i<=n;i++) a[i]=lower_bound(c+1, c+n+1, a[i])-c;
		//for (int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
		up.init(n+10);dw.init(n+10);
		for (int i=1;i<=n;i++)
		{
			ld[i]=dw.ask(a[i]-1);
			lu[i]=up.ask(a[i]+1);
			dw.add(a[i],1);
			up.add(a[i],1);
		}
		dw.clear(); up.clear();
		for (int i=n;i>=1;i--)
		{
			rd[i]=dw.ask(a[i]-1);
			ru[i]=up.ask(a[i]+1);
			dw.add(a[i],1);
			up.add(a[i],1);
		}
		s1=s2=t1=t2=t3=t4=0;
		for (int i=1;i<=n;i++)
		{
			s1+=ru[i];
			s2+=rd[i];
			t1+=lu[i]*ld[i];
			t2+=ru[i]*rd[i];
			t3+=lu[i]*ru[i];
			t4+=ld[i]*rd[i];
		}
		ans=s1*s2-t1-t2-t3-t4;
		printf("%I64d\n",ans);
	}

	return 0;
}