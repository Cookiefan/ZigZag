#include <bits/stdc++.h>
using namespace std;


class AlmostFibonacciKnapsack
{
public:
	
	vector <int> getIndices(long long x)
	{
		long long num[200];
		int n;
		long long now;
		vector<int> ans;
		ans.clear();
		if (x==1)
		{
			ans.push_back(-1);
			return ans;
		}
		num[1]=2;
		num[2]=3;
		n=2;
		while (num[n]<x) num[++n]=num[n-1]+num[n-2]-1;
		now=x;
		for (int i=n;i>=1;i--)
		{
			if (now==num[i]);
			{
				now-=num[i];
				ans.push_back(num[i]);
			}
			if (now==num[i]+1)
			{
				now-=(num[i]+1);
				ans.push_back(num[i-1]);
				ans.push_back(num[i-2]);
				i--;
			}
			else if (now>num[i])
			{
				now-=num[i];
				ans.push_back(i);
			}
		}
	}
};

int main()
{
	AlmostFibonacciKnapsack q;
	vector<int> ans=q.getIndices(86267769395);
	for (int i=0;i<ans.size();i++) cout<<ans[i]<<' '; cout<<endl;
	return 0;
}