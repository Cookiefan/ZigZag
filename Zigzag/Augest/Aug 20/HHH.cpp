#include <bits/stdc++.h>
using namespace std;
string s, t;
map<string, int> mp;

bool pp(string &s)
{
	int len=s.length();
	for (int i=0;i<len;i++)
		if (s[i]!=s[len-i-1]) return 0;
	return 1;
}
int count(string &s)
{
	mp.clear();
	int len=s.length();
	int tmp=0;
	for (int i=0;i<len;i++)
		for (int j=i;j<len;j++)
		{
			t=s.substr(i, j-i+1);
			if (pp(t))
			{
				if (mp.find(t)==mp.end())
				{
					mp[t]=1;
					tmp++;
				}
			}
		}
	return tmp;
}

int main()
{
	cin>>s;
	printf("%d\n",count(s));
	return 0;
}