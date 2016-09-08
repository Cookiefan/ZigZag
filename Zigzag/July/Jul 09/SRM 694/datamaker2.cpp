#include <bits/stdc++.h>
#define maxn 120
using namespace std;
int main()
{
	freopen("B.in","w",stdout);
	cout<<50<<endl;
	srand(time(0));
	for (int i=1;i<=50;i++)
	{
		for (int j=1;j<=10;j++)
		{
			int a=rand()%26;
			printf("%c",'A'+a);
		}
		cout<<endl;
	}
	return 0;
}