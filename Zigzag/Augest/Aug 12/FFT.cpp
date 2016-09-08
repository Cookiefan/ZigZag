#include <bits/stdc++.h>
#define maxn 202000
using namespace std;
typedef complex<double> cpx;
const double pi=acos(-1.0);
int n,m,num;
cpx a[maxn], b[maxn];
int c[maxn];
string s, t;

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

void fft(cpx *a, int n, int f)
{
	for (int i=0;i<n;i++)
		if (i<rev(i, n))
			swap(a[rev(i, n)], a[i]);
	for (int i=1;i<n;i<<=1)
	{
		cpx wn(cos(pi/i), f*sin(pi/i));
		for (int j=0;j<n;j+=(i<<1))
		{
			cpx w(1, 0);
			for (int k=0;k<i;k++, w*=wn)
			{
				cpx x=a[j+k], y=w*a[j+k+i];
				a[j+k]=x+y;
				a[j+k+i]=x-y;
			}
		}
	}
	if (f==-1) for (int i=0;i<n;i++) a[i]/=n;
}


int main()
{
	while (cin>>s)
	{
		memset(c,0,sizeof(c));
		n=s.length();
		cin>>t;
		m=t.length();
		int num=1;
		while (num<max(n,m)) num<<=1;
		num<<=1;
		for (int i=0;i<num;i++)
		{
			a[i]=i<n?s[n-i-1]-'0':cpx(0,0);
			b[i]=i<m?t[m-i-1]-'0':cpx(0,0);
		}
		fft(a, num, 1);
		fft(b, num, 1);
		for (int i=0;i<num;i++) a[i]*=b[i];
		fft(a, num, -1);
		for (int i=0;i<num;i++) c[i]=(int)(a[i].real()+0.5);
		for (int i=0;i<num;i++)
		{
			c[i+1]+=c[i]/10;
			c[i]%=10;
		}
		while (c[num]>0) num++;
		while (c[num-1]==0 && num>1) num--;
		for (int i=num-1;i>=0;i--) printf("%d", c[i]);
		printf("\n");
	}
	return 0;
}