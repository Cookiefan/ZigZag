#include <bits/stdc++.h>
using namespace std;

int main()
{
	int now=0;
	for (int i=1;i<=1000000000;i++)
	{
		if ((int)(i-sqrt(i))>now)
		{
			now=i-sqrt(i);
			cout<<i<<' '<<now<<endl;
		}
	}
	return 0;
}