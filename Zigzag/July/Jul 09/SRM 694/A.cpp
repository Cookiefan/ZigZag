#include <bits/stdc++.h>
#define maxn 12000
using namespace std;

class MakingPairs
{
	int get(vector <int> card)
	{
		int n=card.size(), ans=0;
		for (int i=0;i<n;i++)
		{
			ans+=card[i]/2;
		}
		return ans;
	}
};

int main()
{



	return 0;
}