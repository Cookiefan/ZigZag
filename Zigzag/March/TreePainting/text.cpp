#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 120000
using namespace std;
int dg[maxn];
int n,f,g,x;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		int ans1=0, ans2=0, f=0,g=0;
		memset(dg,0,sizeof(dg));
		for (int i=1;i<n;i++)
		{
			scanf("%d",&x);
			dg[x]++; dg[i]++;
		}
		for (int i=0;i<n;i++)
		{
			if (dg[i]==1)
				f++;
			if (dg[i]%2)
				g++;
		}
		ans1+=(dg[0]+1)/2;
		for (int i=1;i<n;i++) ans1+=(dg[i]-1)/2;
		ans1=g/2;
		ans2=(f+1)/2;
		cout<<ans2<<' '<<ans1<<endl;
	}
	return 0;
}