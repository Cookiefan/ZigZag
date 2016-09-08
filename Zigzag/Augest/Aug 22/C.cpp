#include <bits/stdc++.h>
using namespace std;

int a[5],b[5];
int n;
typedef pair<int,int> pii;
vector<pii> w, b;
vector<int> p;
map<int, int> link[2200];
int chose[30000];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d%d%d%d",&a[0],&a[1],&a[2],&b[0],&b[1],&b[2]);
		n=a[0]+a[1]+a[2];
		if (a[1]&1)
		{
			printf("-1\n");
			continue;
		}
		if (a[2]>=3)
		{
			for (int i=1;i<a[2];i++)
				w.push_back(pii(i, i+1));
			w.push_back(pii(a[2], 1));
			for (int i=1;i<=a[1];i+=2)
				w.push_back(pii(a[2]+i, a[2]+i+1));
		}
		else
		{
			if (!a[1])
			{
				printf("-1\n");
				continue;
			}
			w.push_back(a[2]+1, 1);
			if (a[2]>1) w.push_back(1, a[2]);
			w.push_back(a[2], a[2]+1);
			for (int i=3;i<=a[1];i+=2)
				w.push_back(pii(a[2]+i, a[2]+i+1));
		}
		for (auto e:w)
		{
			link[e.first][e.second]=1;
			link[e.second][e.first]=1;
		}

		if (b[1]&1)
		{
			printf("-1\n");
			continue;
		}
		if (b[2]>=3)
		{
			int now=1;
			for (int i=1;i<=b[2];i++)
				if ()
		}
		




	}

	return 0;
}