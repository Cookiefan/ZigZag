#include <bits/stdc++.h>
#define maxn 500
using namespace std;

typedef long long LL;
LL oo=1000000007;
typedef vector<int> bs;
map<bs, LL> mp;
typedef pair<bs, LL> pbi;
bs b[maxn];
LL a[maxn], ans;
vector<int> prime;
int np[5000];
int num, n;


void get_prime(int n)
{
	memset(np,0,sizeof(np));
	for (int i=2;i<=n;i++)
	{
		if (!np[i])
			prime.push_back(i);
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)
				break;
		}
	}
}

int main()
{
	get_prime(2001);
	num=prime.size();
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%I64d",&a[i]);
		for (int i=1;i<=n;i++)
		{
			b[i].clear();
			for (int j=0;j<num;j++)	
			{
				int tmp=0;			
				while (a[i]%prime[j]==0)
				{
					a[i]/=prime[j];
					tmp^=1;
				}
				b[i].push_back(tmp);
			}
		}
		mp.clear();
		bs zero;
		zero.clear();
		for (int j=0;j<num;j++) zero.push_back(0);
		mp[zero]=1;
		vector<pbi> q;
		for (int i=1;i<=n;i++)
		{
			q.clear();
			for (auto j:mp) q.push_back(j);
			int ss=q.size();
			for (int j=0;j<ss;j++)
			{
				bs now=q[j].first;
				LL sum=q[j].second;
				for (int k=0;k<num;k++)
				{
					//cout<<now[k]<<' ';
					now[k]^=b[i][k];
				}
				//cout<<sum<<endl;
				if (mp.find(now)==mp.end()) mp[now]=0;
				(mp[now]+=sum)%=oo;
			}
		}
		ans=mp[zero]-1;
		printf("Case #%d:\n%I64d\n",o,ans);
	}
	return 0;
}