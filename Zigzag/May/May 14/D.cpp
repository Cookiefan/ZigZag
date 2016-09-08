#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <map>
#define maxn 120000

using namespace std;
string s;
map<string, int> mp;

int main()
{
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		cin>>s;
		sort(s.begin(), s.end());
		if (mp.find(s)==mp.end())
			mp[s]=0;
		printf("%d\n",mp[s]);
		mp[s]++;
	}
	return 0;
}