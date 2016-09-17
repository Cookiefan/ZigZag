#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL v[20][100];
LL dp[100][20][100];
int a[100], b[10];
int n, m;


void pre()
{
  memset(dp, 0, sizeof(dp));
  memset(v, 0, sizeof(v));
  dp[0][0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= 10; j++)
    {
      for (int s = 0; s <= 87; s++)
      {
        dp[i][j][s] = 0;
        LL pre = s-a[i];
        if (pre < 0) continue;
        for (int t = 0; t < i; t++)
          dp[i][j][s] += dp[t][j-1][pre];
      }
    }
}


LL count(int id, int x)
{
	if (x<0) return 0;
	return v[id][x];
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		pre();
		scanf("%d",&m);
		int x, y, z;
		for (int p=1;p<=m;p++)
		{
			scanf("%d%d%d",&x, &y, &z);
			b[0]=a[x]; b[1]=a[y]; b[2]=a[z];
			sort(b, b+3);
			cout<<b[0]<<' '<<b[1]<<' '<<b[2]<<endl;
			LL tmp=count(10, 87);
			cout<<tmp<<endl;
			if (b[0]==b[1] && b[1]==b[2])
			{
				x=b[0];
				tmp=tmp-count(9,87-x);
			}
			else if (b[0]<b[1] && b[1]<b[2])
			{
				x=b[0], y=b[1], z=b[2];
				tmp=tmp-count(9,87-x)-count(9,87-y)-count(9,87-z);
				cout<<tmp<<endl;
				tmp=tmp+count(8,87-x-y)+count(8,87-x-z)+count(8,87-y-z);
				cout<<tmp<<endl;
				tmp=tmp-count(7,87-x-y-z);
				cout<<tmp<<endl;
			}
			else
			{
				x=b[0], y=b[2];
				tmp=tmp-count(9,87-x)-count(9,87-y);
				tmp=tmp+count(8,87-x-y);
			}
			cout<<tmp<<endl;
			if (tmp<=0) printf("No\n");
			else printf("Yes\n");
		}
	}
	return 0;
}