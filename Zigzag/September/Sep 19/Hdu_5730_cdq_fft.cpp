#include <bits/stdc++.h>
#define maxn 400200
#define mod 313
#define PI acos(-1.0)//acosl(-1.0)
using namespace std;
typedef double LD;//long double
typedef long long LL;
//typedef complex<LD> cpx;
struct cpx
{
	LD x, y;
	cpx(){}
	cpx(LD x, LD y):x(x),y(y){}
};
cpx operator +(cpx a, cpx b)
{
	return cpx(a.x+b.x, a.y+b.y);
}
cpx operator -(cpx a, cpx b)
{
	return cpx(a.x-b.x, a.y-b.y);
}
cpx operator *(cpx a, cpx b)
{
	return cpx(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}

int rev(int x, int n)
{
	int tmp=0;
	for (int i=1;i<n;i<<=1)
		if (x & i) tmp=tmp<<1|1;
		else tmp=tmp<<1;
	return tmp;
}

void fft(cpx *a, int n, int flag)
{
	for (int i=0;i<n;i++)
		if (i<rev(i, n))
			swap(a[rev(i, n)], a[i]);
	for (int i=1;i<n;i<<=1)
	{
		cpx wn(cos(PI/i), flag*sin(PI/i));
		//cpx wn(cosl(PI/i), flag*sinl(PI/i));
		for (int j=0;j<n;j+=(i<<1))
		{
			cpx w(1, 0);
			for (int k=0;k<i;k++, w=w*wn)
			{
				cpx x=a[j+k], y=w*a[j+k+i];
				a[j+k]=x+y;
				a[j+k+i]=x-y;
			}
		}
	}
	if (flag==-1) 
		for (int i=0;i<n;i++)
			a[i].x/=n, a[i].y/=n;
}

cpx A[maxn], B[maxn];
int a[maxn];
int dp[maxn], s[maxn], t[maxn], tmp[maxn];
int n;
void roll(int *a, int *b, int *c, int n, int m)
{
	int num=1;
	while (num<n+m) num<<=1;//move out if slow
	for (int i=0;i<num;i++) A[i]=(i<n)?cpx(a[i],0):cpx(0,0);
	for (int i=0;i<num;i++) B[i]=(i<m)?cpx(b[i],0):cpx(0,0);	
	fft(A, num, 1);
	fft(B, num, 1);
	for (int i=0;i<num;i++) A[i]=A[i]*B[i];
	fft(A, num, -1);
	for (int i=0;i<num;i++) c[i]=(LL)(A[i].x+0.5)%mod;
}

void solve(int l, int r)
{
	if (l==r) return ;
	int mid=(l+r)>>1;
	solve(l, mid);
	for (int i=0;i<mid-l+1;i++)
		s[i]=dp[l+i];
	for (int i=0;i<r-l+1;i++)
		t[i]=a[i+1];
	roll(s, t, tmp, mid-l+1, r-l+1);
	for (int i=mid+1;i<=r;i++)
		(dp[i]+=tmp[i-l-1])%=mod;
	solve(mid+1, r);
}

int main()
{
	while (scanf("%d",&n)&&n!=0)
	{
		for (int i=1;i<=n;i++) scanf("%d",&a[i]), a[i]%=mod;
		memset(dp,0,sizeof(dp));
		for (int i=1;i<=n;i++) dp[i]=a[i];
		solve(1, n);
		printf("%d\n",dp[n]);
	}
	return 0;
}