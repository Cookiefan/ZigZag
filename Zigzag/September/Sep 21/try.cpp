#include <bits/stdc++.h>
using namespace std;

int main()
{
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