#include <bits/stdc++.h>
using namespace std;

int v[20];

int main()
{
	int sum=0;
	for (int i=1;i<=100;i++)
	{
		int flag=0;
		for (int j=1;j<=i+2;j++)
			if ((i%j)!=0)
			{
				if (flag==0) flag=1;
				else
				{   sum+=j;
					v[j]++;
					printf("%d %d\n",i, j);
					break;
				}
			}

	}
	return 0;
}