#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("2.in","w",stdout);
	for (int o=1;o<=10;o++)
	{
		cout<<50000<<' '<<5<<endl;
		for (int i=1;i<=50000;i++)
		{
			for (int j=1;j<=5;j++)
				cout<<rand()%10000<<' ';
			cout<<endl;
		}
		cout<<10000<<endl;
		for (int i=1;i<=10000;i++)
		{
			for (int j=1;j<=5;j++)
				cout<<rand()%10000<<' ';
			cout<<endl;
			cout<<rand()%10+1<<endl;
		}
	}
	return 0;
}