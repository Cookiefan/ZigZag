#include <bits/stdc++.h>
using namespace std;

typedef bitset<1005> bs;
bs a,b;
string s,t;

bool operator <=(bs &a, bs &b)
{
	int ss=a.size();
	for (int i=ss;i>=0;i--)
	{
		if (a[i]>b[i]) return 0;
		if (a[i]<b[i]) return 1;
	}
	return 1;
}

bs operator -(bs a, bs b)
{
	int ss=a.size();
	a.flip();
	for (int i=0;i<ss;i++)
		if (a[i]==0)
		{
			a[i]=1;
			break;
		}
		else
			a[i]=0;
	b.flip();
	for (int i=0;i<ss;i++)
		if (b[i]==0)
		{
			b[i]=1;
			break;
		}
		else
			b[i]=0;
	bs c(0);
	for (int i=0;i<ss;i++)
	{
		a[i]=a[i]^b[i]^c[i];
		if (a[i]+b[i]+c[i]>1)
			c[i+1]=1;
	}
	a.flip();
	for (int i=0;i<ss;i++)
		if (a[i]==0)
		{
			a[i]=1;
			break;
		}
		else
			a[i]=0;
	return a;
}

bs gcd(bs a, bs b)
{
	if (b<=a) swap(a, b);
	while (a.any())
	{
		while (a<=b) b=b-a;
		swap(a, b);
	}
	return b;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		cin>>s;
		cin>>t;
		bs a(s);
		bs b(t);
		bs c=gcd(a,b);
		int k=c.size(), flag=0;
		cout<<"Case #"<<o<<": "<<endl;
		for (int i=k-1;i>=0;i--)
		{
			if (c[i]==1) flag=1;
			if (flag) cout<<c[i];
		}
		cout<<endl;
	}

	return 0;
}