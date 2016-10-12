#include <bits/stdc++.h>
using namespace std;

char st[120000];
vector<int> v[256];
vector<char> ans;
set<int> s;
typedef set<int>::iterator sit;
int n, m, num;

bool judge()
{
	for (int x:s)
	{
		if (x==0) continue;
		sit pre=s.lower_bound(x);
		pre--;
		if (x-*pre>m) return 0;
	}
	return 1;
}

int main()
{
	scanf("%d",&m);
	scanf(" %s",st);
	n=strlen(st);
	for (int i=0;i<n;i++) v[st[i]].push_back(i+1);
	s.clear(); s.insert(0); s.insert(n+1);
	for (int w=97;w<=122;w++)
	{
		//cout<<(char)w<<endl;
		if (!v[w].size()) continue;
		for (int i=0;i<v[w].size();i++)
			s.insert(v[w][i]);
		if (judge())
		{
			for (int i=0;i<v[w].size();i++)
			{
				sit now=s.lower_bound(v[w][i]), nxt=now,pre=now;
				nxt++; pre--;
				if (*nxt-*pre<=m)
					s.erase(now);
			}
			break;
		}
	}	
	for (int x:s)
		if (1<=x && x<=n)
			ans.push_back(st[x-1]);
	sort(ans.begin(), ans.end());
	for (int i=0;i<ans.size();i++)
		printf("%c",ans[i]);
	printf("\n");
	return 0;
}