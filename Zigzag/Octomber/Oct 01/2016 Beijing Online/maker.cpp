#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("FF.in","w",stdout);
	cout<<1<<endl;
	int n;
	cout<<(n=60000)<<endl;
	for (int i=0;i<n;i++)
		cout<<((i&1)?1000000:0)<<' ';
	cout<<endl;
	for (int i=0;i<n;i++)
		cout<<((i&1)?0:1000000)<<' ';


	return 0;
}