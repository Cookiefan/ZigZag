#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("C.in","w",stdout);
	cout<<10<<endl;
	int n=100000;
	for (int j=1;j<=10;j++)
	{
		cout<<n<<endl;
		for (int i=1;i<=n;i++) cout<<1<<' '; cout<<endl;
		for (int i=2;i<=n;i++)
			cout<<i<<' '<<(int)sqrt(i)<<' '<<1<<endl;
	}
	return 0;
}