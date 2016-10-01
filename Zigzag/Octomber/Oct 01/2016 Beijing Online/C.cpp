#include <bits/stdc++.h>
using namespace std;

typedef pair<string,string> pss;
map<pss, int> mp;
string now, last;

int main()
{
	//freopen("C.in","r",stdin);
	char c;
	while (scanf("%c",&c)!=EOF)
	{
		if (c=='#') continue;
		now.clear();
		last.clear();
		mp.clear();
		while (c!='#')
		{
			if (islower(c))
				now.push_back(c);
			else
			{
				if (last.length() && now.length())
				{
					pss tmp(last,now);
					//cout<<last<<' '<<now<<endl;
					if (!mp.count(tmp)) mp[tmp]=0;
					mp[tmp]++;
				}
				if (c==' ')
					last=(now.length())?now:last;
				else
					last.clear();
				now.clear();
			}
			scanf("%c",&c);
		}
		pss st;
		int ans=0;
		for (auto tmp:mp)
		{
			if (tmp.second>ans)
			{
				st=tmp.first;
				ans=tmp.second;
			}
		}
		cout<<st.first<<' '<<st.second<<":"<<ans<<endl;	
	}
	return 0;
}