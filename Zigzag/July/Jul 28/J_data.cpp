#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("J.in","w",stdout);
	cout<<1<<endl;
	int n=100000;
	cout<<n<<endl;
	for (int i=1;i<=n;i++)
		if ((i&1)==0) cout<<0<<' '; else cout<<i<<' ';
	cout<<endl;
	return 0;
}