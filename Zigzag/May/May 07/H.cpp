#include <bits/stdc++.h>
#define maxn 520000
using namespace std;

string s;
int n,m;

int main()
{
	char c;
	s.clear();
	while (scanf("%c",&c)==1)
	{
		if (c=='\n') break;
		else s.push_back(c);
	}
	n=s.length();
	scanf("%d",&m);
	int x, now=0, t=1;
	for (int i=1;i<=m;i++)
	{
		t=t*(-1);
		scanf("%d",&x);
		now=(now+t*x+n)%n;
	}

	if (t==1)
	{
		for (int i=n-now;i<n;i++)
			cout<<s[i];
		for (int i=0;i<n-now;i++)
			cout<<s[i];
		cout<<endl;
	}
	else
	{
		now=(2*n-now)%n;
		for (int i=now-1;i>=0;i--)
			cout<<s[i];
		for (int i=n-1;i>=now;i--)
			cout<<s[i];
		cout<<endl;
	}
	return 0;
}