#include <bits/stdc++.h>
using namespace std;

class SumFullSet
{
public:
	string isSumFullSet(vector <int> elements)
	{
		int v[501], n=elements.size();
		memset(v,0,sizeof(v));
		for (int i=0;i<n;i++)
			elements[i]=elements[i]+100;
		for (int i=0;i<n;i++)
			v[elements[i]]=1;
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
				if (v[elements[i]+elements[j]-100]==0)
					return "not closed";
		return "closed";
	}
}query;

int main()
{
	vector<int> a;
	a.push_back(-50);
	a.push_back(-50);
	cout<<query.isSumFullSet(a);
	return 0;
}