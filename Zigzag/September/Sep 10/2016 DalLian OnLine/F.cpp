#include <bits/stdc++.h>
#define maxn 100200
using namespace std;
int a[maxn];
int s[maxn];

bool cmp(int a, int b)
{
	return a>b;
}

int main()
{
	
	int CNT;
	while (scanf("%d",&CNT)!=EOF)
	for (int k=1;k<=CNT;k++)
	{
		int n;
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1, a+n+1, cmp);
		bool flag=1;
		s[0]=0;
		for (int i=1;i<=n;i++)
		{
			s[i]=s[i-1]+a[i];
			//cout<<a[i]<<endl;
			if (!(i*(i-1)<=s[i] && s[i]<=i*(i-1)+2*i*(n-i)))
			{
				flag=0;
				break;
			}
		}
		printf(flag?"T\n":"F\n");
	}
	return 0;
}