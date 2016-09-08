#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("D.in","w",stdout);
	srand(time(0));
	int n=100000;
	long long m=(long long)n*(n-1)/2;;
	cout<<n<<' '<<m<<endl;
	for (int i=1;i<=n;i++)
		cout<<rand()%1000000000+1<<' ';
	return 0;
}