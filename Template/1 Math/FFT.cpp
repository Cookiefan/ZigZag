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
	for (int i=0,j=i;i<n;i++,j=rev(i, n))
		if (i<j) swap(a[i], a[j]);
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

cpx A[maxn], B[maxn];
int a[maxn], b[maxn], c[maxn];
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
