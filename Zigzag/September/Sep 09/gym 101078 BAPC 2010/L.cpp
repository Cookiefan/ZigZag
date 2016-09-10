#include <bits/stdc++.h>
#define maxn 10020
using namespace std;

int a[maxn];
vector<int> pos[2];
string s;

int main()
{
	cin>>s;
	int cnt=0, len=s.length();
	for (int i=0;i<len;i++)
		if (s[i]=='0')
		{
			pos[0].push_back(i);
			cnt++;
		}
		else
			pos[1].push_back(i);
	double ans=0;
	int j=pos[0].size()-1;
	for (int i=0;i<cnt;i++)
		if (s[i]=='1')
		{
			ans+=sqrt(pos[0][j]-i);
			j--;
		}
	printf("%.10f\n",ans);
	return 0;
}