#include <bits/stdc++.h>
using namespace std;

typedef long long llg;
map<llg, llg>mp;
int m;
llg x,y,z;

void add(llg a, llg d)
{
	if (mp.find(a)==mp.end()) mp[a]=0;
	mp[a]+=d;
}
llg val(llg a)
{
	if (mp.find(a)==mp.end()) return 0;
	else return mp[a];
}

int main()
{
	scanf("%d",&m);
	int sign;
	mp.clear();
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&sign);
		if (sign==1)
		{
			scanf("%I64d%I64d%I64d",&x,&y,&z);
			while (x!=y)
			{
				if (x>y) add(x,z), x=x/2;
				else if (x<y) add(y,z), y=y/2;
			}
		}
		else
		{
			llg ans=0;
			scanf("%I64d%I64d",&x,&y);
			while (x!=y)
			{
				if (x>y) ans+=val(x), x=x/2;
				else if (x<y) ans+=val(y), y=y/2;
			}
			printf("%I64d\n",ans);
		}
	}

	return 0;
}