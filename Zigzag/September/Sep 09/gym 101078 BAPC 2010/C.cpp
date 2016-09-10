#include <bits/stdc++.h>
#define oo 10007
using namespace std;

int n;
const int f[512]={
	0,4,0,0,4,0,0,3,0,0,0,0,0,1,0,0,2,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
	0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,4,0,0,1,0,0,2,0,0,3,0,0,2,0,0,2,0,0,1,0,0,0,0,0,1,0,0,1,0,0,
	0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,2,0,0,1,0,0,2,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,2,0,0,3,0,0,2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,
	0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,3,0,0,1,0,0,1,0,0,2,0,0,1,0,0,1,0,0,1,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1
};

const int ms=512;
int dp[5020][ms];
int tr[ms][ms];

int main()
{
	int mxm=(1<<9)-1;
	for (int s=0;s<=mxm;s++)
		for (int t=0;t<=mxm;t++)
		{
			int ok=1;
			for (int i=0;i<9;i++)
				if (((s>>i)&1) && ((t>>i)&1))
				{
					ok=0;
					break;
				}
			tr[s][t]=f[s|t]*ok;
		}
	freopen("ANS.out","w",stdout);
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for (int i=0;i<=5000;i++)
	{
		for (int s=0;s<=mxm;s++)
			for (int t=0;t<=mxm;t++)
				(dp[i+1][t]+=dp[i][s]*tr[s][t]%oo)%=oo;
		cout<<dp[i][0]<<',';
	}
	return 0;
}