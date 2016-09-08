#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#define maxn 10020
#define inf 999999999
using namespace std;

int a[maxn],s[maxn];
int f[maxn];


int n,m,l;

bool judge(int limit)
{
	memset(f,0,sizeof(f));
	f[0]=1;
	for (int i=1;i<=n;i++)
		for (int j=max(0,i-l);j<i;j++)
			if ((s[i]^s[j])>=limit)
				f[i]|=f[j]<<1;
	return f[n]&(1<<m);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&l);
		int l=0, r=0, ans;
		for (int i=1;i<=n;i++) scanf("%d",&a[i]), r=max(r, a[i]);
		s[0]=0;
		for (int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
		r=1<<((int)log2(r)+1);
		while (l<=r)
		{
			int mid=(l+r)>>1;
			//cout<<mid<<endl;
			if (judge(mid))
			{
				l=mid+1;
				ans=mid;
			}
			else
				r=mid-1;
		}
		printf("Case #%d:\n%d\n",o,ans);
	}
	return 0;
}