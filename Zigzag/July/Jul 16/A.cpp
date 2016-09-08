#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef set<pii>::iterator ip;
set<pii> s[50];
int a[120000][50];
int n, m, dim;
int x[10],y[10],sign,p;

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		dim=1<<m;
		for (int k=0;k<dim;k++) s[k].clear();
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&sign);
			if (sign==0)
			{
				for (int j=0;j<m;j++) scanf("%d",&x[j]);
				for (int k=0;k<dim;k++)
				{
					int tmp=k, sum=0;
					for (int j=0;j<m;j++)
					{
						y[j]=(tmp&1)?1:-1;
						tmp>>=1;
					}
					for (int j=0;j<m;j++) sum+=x[j]*y[j];
					s[k].insert(pii(sum, i));
					a[i][k]=sum;
				}
			}
			else
			{
				scanf("%d",&p);
				for (int k=0;k<dim;k++)
				{
					pii tmp=pii(a[p][k], p);
					s[k].erase(tmp);
				}
			}
			int ans=0, tmp=0;
			for (int k=0;k<dim;k++)
			{
				ip l=s[k].begin(), r=s[k].end(); r--;
				tmp=(r->first)-(l->first);
				ans=max(ans, tmp);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
