#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("text.in","r",stdin);
	freopen("text.out","w",stdout);
	string s;
	char c;
	while (c=getchar())
	{
		if (c<='z' && c>='a') s.push_back(c);
		else
		{
			if (s!="and" && s!="of")
				s[0]+='A'-'a';
			cout<<s;
			cout<<c;
			s.clear();
		}
	}
	return 0;
}