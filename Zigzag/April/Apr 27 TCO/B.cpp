#include <bits/stdc++.h>
using namespace std;

class ThreeProgrammers
{
public:
	int a[5],q[220];
	string ans,s;
	bool flag;
	int f[70][70][70][5][5];
	void get_ans(int a, int b, int c,int x, int y)
	{
		if (f[a][b][c][x][y]==0) return ;
		else
		{
			if (a==0 && b==0 && c==0)
			{
				flag=1;
				return ;
			}
			if (c>0 && x!=2 && y!=2) get_ans(a, b, c-1, 2, x);
			if (flag)
			{
				ans.push_back('C');
				return ;
			}
			if (b>0 && x!=1) get_ans(a, b-1, c, 1, x);
			if (flag)
			{
				ans.push_back('B');
				return ;
			}
			if (a>0) get_ans(a-1, b, c, 0, x);
			if (flag)
			{
				ans.push_back('A');
				return ;
			}
			f[a][b][c][x][y]=0;
		}
	}
	string validCodeHistory(string code)
	{
		int len=code.length();
		memset(f,-1,sizeof(f));
		memset(a,0,sizeof(a));
		for (int i=0;i<len;i++)
			a[code[i]-'A']++;
		ans.clear();
		flag=0;
		get_ans(a[0],a[1],a[2], 3, 3);
		if (!flag)
			return "impossible";
		else
		{
			reverse(ans.begin(), ans.end());
			return ans;
		}
	}
}query;

int main()
{
	string t;
	cin>>t;
	cout<<query.validCodeHistory(t);
	return 0;
}
