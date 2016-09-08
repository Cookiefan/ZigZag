#include <bits/stdc++.h>
#define maxn 320
using namespace std;

class
{
public:
	vector<int> t[maxn];
	deque<int> q;
	int f[maxn];
	int countSubtrees(vector <int> a, vector <int> b)
	{
		int n=a.size();
		for (int i=0;i<n;i++) t.clear();
		for (int i=0;i<n;i++)
		{
			t[a[i]].push_back(b[i]);
			t[b[i]].push_back(a[i]);
		}
		q.push_back(1);
		while (!q.empty())
		{
			int x=q.front();


		}



	}
};