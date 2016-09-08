#include <bits/stdc++.h>
#define maxn 120000
#define inf 999999999
using namespace std;
int n,m;
string s;
map<string, int> name;
string abrv[maxn];
char c;


string cut(int x, int y)
{
	string tmp;
	tmp.clear();
	for (int i=1;i<=y;i++)
	{
		
	}
	return tmp;
}

int main()
{
	name.clear();
	for (int i=1989;i<=99999;i++)
	{
		string tmp, now;
		tmp.clear();
		int x=i;
		for (int j=1;j<=4;j++)
		{
			tmp.push_back(x%10+'0');
			now=tmp;
			reverse(now.begin(), now.end());
			x=x/10;
			if (name.find(now)==name.end())
			{
				name[now]=i;
				break;
			}
		}
	}
	scanf("%d",&n);
	for (int o=1;o<=n;o++)
	{
		s.clear();
		while (scanf("%c",&c) && (c<'0' || c>'9'));
		while ('0'<=c && c<='9')
		{
			s.push_back(c);
			scanf("%c",&c);
		}
		if (name.find(s)==name.end())
		{
			string t=s;
			while (t.length()>4 && t[0]=='1') t.erase(t.begin());
			if (t[0]=='0' || (name.find(t)!=name.end() && name[t]/10000>0))
				s.insert(s.begin(),'1');
			cout<<s<<endl;
		}
		else
		{
			cout<<name[s]<<endl;
		}
	}

	return 0;
}