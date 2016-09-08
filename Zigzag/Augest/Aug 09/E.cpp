#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
typedef pair<int,int> pii;
vector<pii> e;

pii p[maxn];
int n;
bool flag;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&p[i].first);
			p[i].second=i;
		}
		sort(p+1,p+n+1);
		flag=1;
		e.clear();
		for (int i=1;i<=n;i++)
		{
			if (p[i].first>i-1)
			{
				flag=0;
				break;
			}
			for (int j=1;j<=p[i].first;j++)
			{
				e.push_back(pii(p[i].second, p[j].second));
			}
		}
		printf("Case #%d: ",o);
		if (!flag)
		{
			printf("No\n");
		}
		else
		{
			printf("Yes\n");
			int ss=e.size();
			printf("%d\n",ss);
			for (int i=0;i<ss;i++)
				printf("%d %d\n",e[i].first, e[i].second);
		}
	}
	return 0;
}