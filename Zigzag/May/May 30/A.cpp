#include <bits/stdc++.h>
using namespace std;

class Plusonegame
{
public:
	int v[12];
	string getorder(string s)
	{
		string t;
		t.clear();
		memset(v,0,sizeof(v));
		int len=s.length();
		for (int i=0;i<len;i++)
		{
			if (s[i]=='+') v[10]++;
			else v[s[i]-'0']++;
		}
		for (int i=0;i<10;i++)
		{
			while (v[i]>0) t.push_back('0'+i), v[i]--;
			if (v[10]>0) t.push_back('+'), v[10]--;
		}
		while (v[10]>0) t.push_back('+'), v[10]--;
		return t;
	}
};