#include <bits/stdc++.h>
#define maxn 420
#define inf 99999999
using namespace std;

int dp[maxn][256], sum[maxn];
int a[maxn];
int n;

void update(int &x, int z)
{
	x=max(x, z);
}
void write(int x)
{
	cout<<"(";
	for (int i=0;i<4;i++)
	{
		cout<<(x&3);
		x>>=2;
	}
	cout<<") ";
}
int main()
{
	//freopen("H.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int x; char c;
		memset(a,0,sizeof(a));
		memset(sum,0,sizeof(sum));
		for (int i=1;i<=n;i++)
		{
			scanf("%d%c",&x,&c);
			if (c=='y') a[x]|=1;
			else if (c=='r') a[x]|=1<<2;
			else if (c=='g') a[x]|=1<<4;
			else a[x]|=1<<6;
			sum[x]++;
		}
		for (int i=0;i<=100;i++)
			for (int msk=0;msk<256;msk++)
				dp[i][msk]=-inf;
		dp[0][0]=0;
		for (int i=1;i<=100;i++)
			for (int msk=0;msk<256;msk++)
			{
				if (dp[i-1][msk]==-inf) continue;
				//炸3
				if (sum[i]==3) update(dp[i][0], dp[i-1][msk]+3*i);
				else if (sum[i]==4)
				{
					//炸4
					update(dp[i][0], dp[i-1][msk]+4*i);
					//炸3留1
					for (int k=0;k<4;k++)
					{
						int cur=0, tmp=3*i;
						int t=(msk>>(k<<1))&3;
						if (t==0) cur=(1<<(k<<1));
						else if (t==1) cur=(2<<(k<<1));
						else if (t==2) cur=(3<<(k<<1)), tmp+=3*i-3;
						else cur=(3<<(k<<1)), tmp+=i;
						update(dp[i][cur], dp[i-1][msk]+tmp);
					}
				}
				//不炸
				int cur=msk, tmp=0;
				for (int k=0;k<4;k++)
				{
					if (!((a[i]>>(k<<1))&3))
					{
						cur&=(~(3<<(k<<1)));
						continue;
					}
					int t=(msk>>(k<<1))&3;
					if (t==0) cur+=(1<<(k<<1));
					else if (t==1) cur+=(1<<(k<<1));
					else if (t==2) cur+=(1<<(k<<1)), tmp+=3*i-3;
					else tmp+=i;				
				}
				//cout<<i<<' '; write(a[i]); write(msk); cout<<dp[i-1][msk]<<' '; write(cur); cout<<tmp<<endl;
				update(dp[i][cur], dp[i-1][msk]+tmp);
			}
		int ans=0;
		for (int msk=0;msk<256;msk++)
			ans=max(ans, dp[100][msk]);
		printf("%d\n",ans);
	}

	return 0;
}