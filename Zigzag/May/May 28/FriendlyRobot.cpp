#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

class FriendlyRobot
{
public:
	int cost[500][500], f[500][500];
	int n;
	void prepare(string s)
	{
		for (int i=1;i<=n;i++)
		{
			int x=0, y=0;
			for (int j=i;j<=n;j++)
			{
				if (s[j]=='L') x--;
				if (s[j]=='R') x++;
				if (s[j]=='U') y--;
				if (s[j]=='D') y++;
				if ((j-i+1)%2==1) cost[i][j]=inf;
				else cost[i][j]=(abs(x)+abs(y))/2;
			}
		}
	}
	int findMaximumReturns(string instructions, int changesAllowed)
	{
		n=instructions.length();
		string s=" "+instructions;
		prepare(s);
		int ans=0;
		memset(f,0,sizeof(f));
		for (int i=1;i<=n;i++)
		{
			if (i%2==1) continue;
			for (int k=0;k<=changesAllowed;k++)
			{
				f[i][k]=-inf;
				for (int j=0;j<i;j++)
				{
					if (j%2==1) continue;
					if (k>=cost[j+1][i])
						f[i][k]=max(f[i][k], f[j][k-cost[j+1][i]]+1);
				}
				ans=max(ans,f[i][k]);
			}
		}
		return ans;
	}
}T;
string s;
int k;

int main()
{
	cin>>s>>k;
	printf("%d\n",T.findMaximumReturns(s,k));

	return 0;
}
