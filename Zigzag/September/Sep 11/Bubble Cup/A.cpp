#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;
const int oo=1000000007;
int main()
{
	int f[1000002];
	f[1]=1; f[2]=1;
	for (int i=3;i<=1000000;i++)
	{
		f[i]=(f[i-1]+f[i-2])%oo;
		if (!mp.count(f[i])) mp[f[i]]=1;
		else printf("%d\n",i);
	}


	return 0;
}