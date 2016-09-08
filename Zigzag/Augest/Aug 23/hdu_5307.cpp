#include <bits/stdc++.h>
#define maxn 400200
using namespace std;

typedef long double LD;
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
cpx operator *(cpx a, LD x)
{
	return cpx(a.x*x, a.y*x);
}

const long double PI=acosl(-1.0);
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

void fft(cpx *a, int n, int flag)
{
	for (int i=0;i<n;i++)
		if (i<rev(i, n))
			swap(a[rev(i, n)], a[i]);
	for (int i=1;i<n;i<<=1)
	{
		cpx wn(cosl(PI/i), flag*sinl(PI/i));
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
	if (flag==-1) for (int i=0;i<n;i++) a[i]=a[i]*(1.0l/n);
}

cpx A[maxn], B[maxn], C[maxn];
void convolution(int *a, int *b, LL *c, int n, int m)
{
	int num=1;
	while (num<n+m) num<<=1;
	for (int i=0;i<num;i++) A[i]=(i<n)?cpx(a[i],0):cpx(0,0);
	for (int i=0;i<num;i++) B[i]=(i<m)?cpx(b[i],0):cpx(0,0);	
	fft(A, num, 1);
	fft(B, num, 1);
	for (int i=0;i<num;i++) C[i]=A[i]*B[i];
	fft(C, num, -1);
	for (int i=0;i<num;i++) c[i]=(LL)(C[i].real()+0.5);
}

int a[maxn], b[maxn], v[maxn], s[maxn];
LL c[maxn], d[maxn], ans[maxn];
int n;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int cnt=0, tmp=0;
		s[0]=ans[0]=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&v[i]);
			if (v[i]==0)
			{
				tmp+=(++cnt);
				ans[0]+=tmp;
			}
			else
				cnt=tmp=0;
			s[i]=s[i-1]+v[i];
		}
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for (int i=0;i<=n;i++)
		{
			a[s[i]]+=i;
			b[s[n]-s[i]]+=1;
		}
		convolution(a,b,c,s[n]+1,s[n]+1);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for (int i=0;i<=n;i++)
		{
			a[s[n]-s[i]]+=i;
			b[s[i]]+=1;
		}
		convolution(a,b,d,s[n]+1,s[n]+1);
		LL *cc=c+s[n], *dd=d+s[n];
		for (int i=1;i<=s[n];i++) ans[i]=cc[i]-dd[i];
		for (int i=0;i<=s[n];i++)
			printf("%I64d\n",ans[i]);
	}
	return 0;
}