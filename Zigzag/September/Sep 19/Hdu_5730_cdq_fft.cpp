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
    for (int i=n>>1;i;i>>=1,x>>=1)
        tmp=tmp<<1|x&1;
    return tmp;
}

void fft(cpx *a, int n, int flag)
{
	for (int i=0;i<n;i++)
		if (i<rev(i, n))
			swap(a[rev(i, n)], a[i]);
	for (int k=1;k<n;k<<=1)
	{
		cpx wn(cos(PI/k), flag*sin(PI/k));
		//cpx wn(cosl(PI/i), flag*sinl(PI/i));
		cpx w(1, 0);
		for (int i=0;i<k;i++,w=w*wn)
			for (int j=i;j<n;j+=(k<<1))
			{
				cpx x=a[j], y=w*a[j|k];
				a[j]=x+y;
				a[j|k]=x-y;
			}
	}
	if (flag==-1) 
		for (int i=0;i<n;i++)
			a[i].x/=n, a[i].y/=n;
}

// void fft(cpx *a, int n, int flag)
// {
//     if (flag==-1) 
//     {
//     	for (int i=1;i<n/2;i++) swap(a[i], a[n-i]);
//         for (int i=0;i<n;i++) a[i].x/=n, a[i].y/=n;
//     }
//     cpx wn(cos(2*PI/n), sin(2*PI/n));
//     for (int s=n>>1;s;s>>=1, wn=wn*wn)
//     {
//     	cpx w(1,0);
//        	for (int k=0; k<s; k++, w=w*wn)
// 			for (int i=k; i<n; i+=s<<1)
//             {
//                 cpx x=a[i], y=a[i|s];
// 				a[i]=x+y;
// 				a[i|s]=(x-y)*w;
//             }
//     }
//     for (int i=1, j=0;i<n;i++,j=0)
// 	{
// 		for (int s=i, k=n>>1; k; s>>=1, k>>=1)
// 			j=j<<1|s&1;
// 		if (i<j) swap(a[i], a[j]);
// 	}
// }

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