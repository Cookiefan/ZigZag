#include <bits/stdc++.h>
#define maxn 1002000
using namespace std;

long double f[maxn];
char s[maxn];

int main()
{
	long double a=1;
	f[1]=1;
	for (int i=2;i<=1000000;i++)
	{
		a+=1.0/((long double)i*i);
		f[i]=a;
	}
	while(scanf(" %s", s)!=EOF)
	{

		if (strlen(s)>=7)
		{
			cout.setf(ios::fixed);
			cout<<setprecision(5)<<f[1000000]<<endl;
		}
		else
		{
			int len=strlen(s), n=0;
			for (int i=0;i<len;i++)
				n=n*10+s[i]-'0';
			cout.setf(ios::fixed);
			cout<<setprecision(5)<<f[n]<<endl;
		}	
			

	}

	return 0;
}