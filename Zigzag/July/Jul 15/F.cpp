#include <bits/stdc++.h>
#define maxn 520
using namespace std;
typedef long long LL;
string s[maxn];
LL f[maxn][maxn],g[maxn],len[maxn],val[maxn];
LL ins[maxn][maxn];
LL m;
int n;

int main()
{
	scanf("%d%I64d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&val[i]);
	for (int i=1;i<=n;i++)
	{
		cin>>s[i];
		len[i]=s[i].length();
		ins[0][i]=0;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			int l;
			if (i==j)
				l=len[i]-1;
			else
				l=min(len[i], len[j]);
			for (int k=l;k>=0;k--)
				if (s[i].substr(len[i]-k, k)==s[j].substr(0, k))
				{
					ins[i][j]=k;
					break;
				}
		}
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	for (int i=1;i<=201;i++)
	{
		g[i]=0;
		for (int j=1;j<=n;j++)
		{
			for (int k=0;k<=n;k++)
			{
				if (i-len[j]+ins[k][j]>=0 && f[i-len[j]+ins[k][j]][k]!=-1)
				{
					if (i==6) cout<<len[j]<<' '<<ins[k][j]<<' '<<f[i-len[j]+ins[k][j]][k]<<endl;
					f[i][j]=max(f[i][j], f[i-len[j]+ins[k][j]][k]+val[j]);
				}
			}
			g[i]=max(g[i],f[i][j]);
		}
		//cout<<g[i]<<endl;
	}
	for (int i=1;i<=6;i++)
	{
		for (int j=1;j<=3;j++)
			cout<<f[i][j]<<' ';
		cout<<endl;
	}
	LL ans=0;
	for (int i=1;i<=201;i++)
	{
		LL tmp=(LL)(m/i)*g[i]+g[m%i];
		ans=max(ans, tmp);
	}
	printf("%I64d\n",ans);

	return 0;
}