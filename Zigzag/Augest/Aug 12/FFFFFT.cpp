#include <bits/stdc++.h>
#define maxn 202000
using namespace std;
typedef complex<double> cpx;
const double pi=acos(-1.0);
int n,m,num;
cpx a[maxn], b[maxn];
int c[maxn];
string s, t;

int rev(int id, int len)
{
    int ret = 0;
    for(int i = 0; (1 << i) < len; i++)
    {
        ret <<= 1;
        if(id & (1 << i)) ret |= 1;
    }
    return ret;
}

cpx A[140000];
void fft(cpx* a, int len, int DFT)//对a进行DFT或者逆DFT, 结果存在a当中
{
    //Complex* A = new Complex[len]; 这么写会爆栈
    for(int i = 0; i < len; i++)
        A[rev(i, len)] = a[i];
    for(int s = 1; (1 << s) <= len; s++)
    {
        int m = (1 << s);
        cpx wm = cpx(cos(DFT*2*pi/m), sin(DFT*2*pi/m));
        for(int k = 0; k < len; k += m)
        {
            cpx w = cpx(1, 0);
            for(int j = 0; j < (m >> 1); j++)
            {
                cpx t = w*A[k + j + (m >> 1)];
                cpx u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w*wm;
            }
        }
    }
    if(DFT == -1) for(int i = 0; i < len; i++) A[i] /= len;
    for(int i = 0; i < len; i++) a[i] = A[i];
}


int main()
{
	while(cin>>s)
	{
		n=s.length();
		for (int i=0;i<3*n;i++) a[i]=0;
		for (int i=0;i<n;i++) a[i]=s[n-i-1]-'0';
		cin>>t;
		m=t.length();
		for (int i=0;i<3*m;i++) b[i]=0;
		for (int i=0;i<m;i++) b[i]=t[m-i-1]-'0';
		int num=1;
		while (num<max(n,m)) num<<=1;
		num<<=1;

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
		while (c[num-1]==0) num--;
		for (int i=num-1;i>=0;i--) printf("%d", c[i]);
		printf("\n");
	}
	return 0;
}