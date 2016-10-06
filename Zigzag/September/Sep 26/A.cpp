#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

class OthersXor
{
public:
	long long minSum(vector <int> x)
	{
		vector<int> a;
		for (int y:x)
			if (y!=-1)
				a.push_back(y);
		LL tmp=0;
		LL ans=0;
		for (int y:a) tmp^=y;
		
		if (a.size()%2==0)
		{
			for (int y:a)
				ans+=(tmp^y);
			if (a.size()<x.size())
			{
				a.push_back(tmp);
				tmp=0;
				for (int i:a)
					for (int j:a)
						tmp=max(tmp, (LL)i^j);
				ans=min(ans, tmp);
			}
			return ans;
		}
		else
		{
			for (int i:a)
				for (int j:a)
					ans=max(ans, (LL)i^j);
			if (tmp==0)
				return ans;
			else
			{
				if (a.size()<x.size())
				{
					ans+=tmp;
					return ans;
				}
				else
					return -1;
			}
		}

	}

};

int main()
{
	int n;
	vector<int> s;
	scanf("%d",&n);
	int e;
	for (int i=0;i<n;i++)
	{
		cin>>e;
		s.push_back(e);
	}
	OthersXor ans;
	cout<<ans.minSum(s)<<endl;
	
	return 0;
}