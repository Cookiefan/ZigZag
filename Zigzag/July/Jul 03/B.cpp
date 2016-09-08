#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
int a,b,c;
int s[3];

bool judge(int x)
{
	s[0]=a, s[1]=b, s[2]=c;
	if (min(s[0],s[1])<x) return 0;
	s[0]-=x, s[1]-=x;
	sort(s,s+3);
	if (s[0]+s[1]==s[2]) return 2*s[2]>=x;
	else if (s[0]+s[1]>s[2])
		return s[0]+s[1]+s[2]>=x;
	else
		return (s[0]+s[1])*2+1>=x;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&a,&b,&c);
		int l=0, r=a+b+c,ans=0;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (judge(mid))
			{
				l=mid+1;
				ans=mid;
			}
			else
				r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}