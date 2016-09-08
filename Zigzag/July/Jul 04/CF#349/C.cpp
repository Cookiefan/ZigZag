#include <bits/stdc++.h>
#define maxn 120000
using namespace std;
string s;

vector<string> q;
map<string, int> mp;
int v[maxn];
int n, num;

vector<string> dp(int x, string last)
{
	if (v[x] || x>=n) return ;
	v[x]=1;
	string tmp=s.substr(x, 2);
	cout<<tmp<<endl;
	if (tmp!=last && mp.find(tmp)!=mp.end())
	{
		q.push_back(tmp);
		mp[tmp]=1;
		dp(x+2, tmp);
	}
	tmp=s.substr(x, 3);
	cout<<tmp<<endl;
	if (tmp!=last && mp.find(tmp)!=mp.end())
	{
		q.push_back(tmp);
		mp[tmp]=1;
		dp(x+3, tmp);
	}
}

int main()
{
	cin>>s;
	n=s.length();
	for (int i=5;i<n;i++)
		dp(i, "");
	num=q.size();
	cout<<num<<endl;
	for (int i=0;i<num;i++)
		cout<<q[i]<<endl;
	return 0;
}