#include <bits/stdc++.h>
using namespace std;

class BearPasswordAny
{
public:
	string findPassword(vector <int> x)
	{
		string s;
		s.clear();
		int n=x.size(), now=0;
		for (int i=n-1;i>=0;i--)
		{
			if (x[i]<0) return "";
			else
			if (x[i]>0)
			{
				for (int k=1;k<=x[i];k++)
				{
					for (int j=1;j<=i+1;j++)
						s.push_back('a'+now);
					now=now^1;
				}
				int tmp=x[i];
				for (int k=i;k>=0;k--)
					x[k]-=tmp*(i-k+1);
			}
		}
		if (s.length()==n) return s;
		else return "";
	}
}T;

vector<int> a;
int n,x;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		a.push_back(x);
	}
	cout<<T.findPassword(a)<<endl;

	return 0;
}