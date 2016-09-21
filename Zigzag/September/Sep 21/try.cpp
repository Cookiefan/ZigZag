#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef long long LL;
inline LL exp(LL a, LL b, LL p)
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

int main()
{
	int g = 2;
	while (exp(g, (MOD - 1) / 2, MOD) == 1 || exp(g, (MOD - 1) / 479, MOD) == 1) {
	    g ++;
	}
	cout<<g<<endl;
	int n=12;
	for (int i=1;i<=n;i++)
	{
		for (int d=1;d<=i;d++)
			if (i%d==0)
				cout<<d<<' ';
		cout<<endl;
	}
	cout<<endl;
	for (int i=1;i<=n;i++)
	{
		for (int d=1;d<=n/i;d++)
			cout<<d<<' ';
		cout<<endl;
	}
	return 0;
}