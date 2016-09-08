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

int count(int len, int x)
{
	s.clear();
	mp.clear();
	for (int i=0;i<len;i++)
	{
		s.push_back(x&1);
		x>>=1;
	}
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
	int i;
	scanf("%d",&i);
	int ans=i;
	for (int mask=0;mask<(1<<i);mask++)
	{
		int tmp=count(i, mask);
		ans=min(ans, tmp);
		if (tmp==7)
		{
			int tmp=mask;
			for (int j=0;j<i;j++)
			{
				if (tmp&1) cout<<'B';
				else cout<<'A';
				tmp>>=1;
			}
			cout<<endl;
		}
	}
	cout<<ans<<endl;
	return 0;
}