#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

int main()
{
	srand(time(0));
	freopen("E.in","w",stdout);
	cout<<1<<endl;
	cout<<1000<<endl;
	for (int i=1;i<=1000;i++)
	{
		cout<<rand()%20000-10000<<' ';
		cout<<rand()%20000-10000<<endl;
	}

	return 0;
}