#include <bits/stdc++.h>
using namespace std;

set<string> s;
string a;
map<string, int> v;
vector<string> l,h;
int n,m,k;

int main()
{
	scanf("%d",&n);
	s.clear();
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		for (int j=1;j<=k;j++)
		{
			cin>>a;
			if (k>1 && s.find(a)==s.end()) s.insert(a);
		}
	}
	scanf("%d",&m);
	l.clear();
	for (int i=1;i<=m;i++)
	{
		cin>>a;
		if (s.size()==1 || s.find(a)==s.end())
			l.push_back(a);	
	}
	v.clear();
	int num=l.size();
	for (int i=0;i<num;i++)
		if (v.find(l[i])==v.end())
		{
			h.push_back(l[i]);
			v[l[i]]=1;
		}
	num=h.size();
	for (int i=0;i<num;i++)
	{
		cout<<h[i];
		if (i==num-1) cout<<endl;
		else cout<<' ';
	}
	if (!num) printf("No one is handsome\n");

	return 0;
}