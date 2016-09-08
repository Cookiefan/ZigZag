#include <bits/stdc++.h>
using namespace std;

int dp[12][1080];
int b[1080][12];
int tp[12];
int n,m;
int a[12][12];

void judge(int x, int lst, int msk)
{
	bool flag=1;
	for (int i=0;i<m;i++)
	{
		if (i && a[x-1][i-1]==a[x-1][i] && a[x][i])
			flag=flag&(b[lst][i-1]^b[lst][i]);
		if (i && a[x][i-1]==a[x][i] && a[x][i])
			flag=flag&(b[msk][i-1]^b[msk][i]);
		if (a[x-1][i]==a[x][i] && a[x][i])
			flag=flag&(b[lst][i]^b[msk[i]]);
	}
	return flag;
}

int count(int x, int lst, int msk)
{
	int tmp=0;
	if (b[msk][0] && !b[lst][i])
		tmp++;
	for (int i=1;i<m;i++)
		if (b[msk][i] && !b[msk][i-1] && !b[lst][i])
			tmp++;
	return tmp;
}


int main()
{
	for (int msk=0;msk<(1<<10);msk++)
		for (int i=0;i<10;i++)
			b[msk][i]=(msk>>i)&1;
	for (int i=0;i<10;i++)
		tp[i]=1<<i;

	int Case;
	scanf("%d",&Case);
	char c;
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		memset(a, 0, sizeof(a));
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				scanf("%c",&c);
				if (c=='.') a[i][j]=0;
				else a[i][j]=c-'0'+1;
			}

		for (int i=0;i<n;i++)
			for (msk=0;msk<(1<<m);msk++)
				for (lst=0;lst<(1<<m);lst++)
					if (judge(i, lst, msk))
						dp[i&1][msk]=max(dp[i][msk], dp[i-1][lst]+count(i, lst, msk));

	}

	return 0;

}