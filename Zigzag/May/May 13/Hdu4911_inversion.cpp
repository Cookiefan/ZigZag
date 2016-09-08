	#include <iostream>
	#include <cstdio>
	#include <algorithm>
	#include <cmath>
	#include <cstring>
	#define maxn 120000
	using namespace std;

	int q[maxn], nq[maxn];
	int n, m;
	long long sum;

	void solve(int l, int r)
	{
		if (l==r) return ;
		int mid=(l+r)>>1;
		solve(l, mid);
		solve(mid+1, r);
		int i=l, j=mid+1, k=0;
		while (i<=mid || j<=r)
		{
			if (j>r || i<=mid && q[i]<=q[j]) nq[k++]=q[i++], sum+=(j-mid-1);
			else
			if (i>mid || j<=r && q[i]>q[j]) nq[k++]=q[j++];
		}
		for (int i=0;i<k;i++) q[l+i]=nq[i];
	}

	int main()
	{
		while (scanf("%d%d",&n,&m)!=EOF)
		{
			sum=0;
			for (int i=1;i<=n;i++) scanf("%d",&q[i]);
			solve(1,n);
			printf("%I64d\n",max(0LL, sum-m));
		}
		return 0;
	}