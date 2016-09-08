#include <bits/stdc++.h>
#define N 131072
#define pi acos(-1)
#define ll long long
using namespace std;
typedef complex<double> E;
int n,m,L;
char ch[N];
int R[N],c[N];
E a[N],b[N];
void fft(E *a,int f)
{
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
		{
			E w(1,0);
			for(int k=0;k<i;k++,w*=wn)
			{
				E x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
		//for (int i=0;i<n;i++) cout<<a[i]<<' '; cout<<endl;
	}
	if(f==-1)for(int i=0;i<n;i++)a[i]/=n;
}
int main()
{
	scanf("%d",&n);n--;
    scanf("%s",ch);
	for(int i=0;i<=n;i++)a[i]=ch[n-i]-'0';
	scanf("%s",ch);
	for(int i=0;i<=n;i++)b[i]=ch[n-i]-'0';
	m=2*n;for(n=1;n<=m;n<<=1)L++;
	for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	fft(a,1);fft(b,1);

	for (int i=0;i<n;i++) cout<<a[i]<<' '; cout<<endl;

	for(int i=0;i<=n;i++)a[i]*=b[i];
	fft(a,-1);
	for(int i=0;i<=m;i++)c[i]=(int)(a[i].real()+0.1);
	for (int i=0;i<=m;i++) cout<<' '<<c[i]; cout<<endl;
	for(int i=0;i<=m;i++)
		if(c[i]>=10)
		{
			c[i+1]+=c[i]/10,c[i]%=10;
			if(i==m)m++;
		}
	for(int i=m;i>=0;i--)printf("%d",c[i]);
	return 0;
}