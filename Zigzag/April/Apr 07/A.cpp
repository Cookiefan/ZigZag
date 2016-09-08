#include <bits/stdc++.h>
using namespace std;


class AlmostFibonacciKnapsack
{
public:
	long long num[200];
	int n;
	long long sum;
	bool flag;
	vector<int> ans;
	void dfs(int k, long long t)
	{
		if (sum==t)
		{
			flag=1;
			int m=ans.size();
			for (int i=0;i<m;i++) cout<<ans[i]<<' ';
			return ;
		}
		if (k>9) return ;
		for (int i=(k?ans[k-1]:0)+1; i<=n; i++)
		{
			if (sum+num[i]>t) break;
			sum+=num[i];
			ans.push_back(i);
			dfs(k+1, t);
			if (flag) return ;
			ans.pop_back();
			sum-=num[i];
		}
	}
	vector <int> getIndices(long long x)
	{
		num[1]=2;
		num[2]=3;
		n=2;
		while (num[n]<x) num[++n]=num[n-1]+num[n-2]-1;
		flag=0, sum=0;
		ans.clear();
		cout<<x<<": ";
		dfs(0, x);
		cout<<endl;
	}
};

int main()
{
	AlmostFibonacciKnapsack q;
	for (int i=1;i<=1000;i++)
		q.getIndices(i);
	return 0;
}