#include <bits/stdc++.h>
#define maxn 100200
using namespace std;

typedef pair<int,int> pii;
const pii p[6]={pii(9, 6), pii(8, 7), pii(7, 3), pii(5, 5), pii(4, 4), pii(1, 2)};
const int v[10]={6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int a[maxn];
int n, sum;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		char c;
		sum=0;
		for (int i=0;i<n;i++)
		{
			scanf(" %c",&c);
			a[i]=c-'0';
			sum+=v[a[i]];
		}
		for (int i=0;i<n;i++)
		{
			int now;
			for (int k=0;k<6;k++)
			{
				int tmp=sum-p[k].second;
				//cout<<k<<' '<<tmp<<endl;
				if (2*(n-i-1)<=tmp && tmp<=7*(n-i-1))
				{
					now=p[k].first;
					sum=tmp;
					break;
				}
			}
			printf("%d",now);
		}
		printf("\n");

	}
	return 0;
}