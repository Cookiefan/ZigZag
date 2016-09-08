#include <bits/stdc++.h>
#define maxn 120
using namespace std;

class DistinguishableSetDiv2
{
public:
	int n,m,ans;
	vector<string> a,name;
	bool judge()
	{
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
				if (name[i]==name[j])
					return 0;
		return 1;
	}
	void dfs(int k)
	{
		if (k>=m)
		{
			if (judge()) ans++;
			return ;
		}
		dfs(k+1);
		for (int i=0;i<n;i++)
			name[i].push_back(a[i][k]);
		dfs(k+1);
		for (int i=0;i<n;i++)
			name[i].erase(name[i].end()-1);
	}
	int count(vector <string> answer)
	{
		a=answer;
		n=a.size(),m=a[0].length();
		for (int i=0;i<n;i++)
			name.push_back("");
		ans=0;
		dfs(0);
		return ans;
	}
}t;
int main()
{
	vector <string> b;
	int n,m;
	scanf("%d",&n);
	string s;
	for (int i=0;i<n;i++)
	{
		cin>>s;
		b.push_back(s);
	}
	printf("%d\n",t.count(b));
	return 0;
}