#include <bits/stdc++.h>
#define maxn 12000
using namespace std;


map<int, int> pos;
int heap[maxn];
int n,m;

void up(int x)
{
	int y=x/2;
	while (y)
	{
		if (heap[x]<heap[y])
		{
			swap(heap[x], heap[y]);
			x=y;
			y=x/2;
		}
		else break;
	}
}

int main()
{
	scanf("%d%d ",&n,&m);

	for (int i=1;i<=n;i++)
	{
		scanf("%d ",&heap[i]);
		up(i);
	}
	pos.clear();
	for (int i=1;i<=n;i++) pos[heap[i]]=i;
	int x,y, ans;
	string word;
	for (int i=1;i<=m;i++)
	{
		// 24 is the root
		// 26 and 23 are siblings
		// 46 is the parent of 23
		// 23 is a child of 10
		scanf(" %d ",&x);
		cin>>word;
		if (word=="and")
		{
			scanf(" %d ",&y);
			cin>>word;
			cin>>word;
			ans=(pos[x]/2==pos[y]/2);
		}
		else
		{
			cin>>word;
			cin>>word;
			if (word=="root")
			{
				ans=(heap[1]==x);
			}
			else if (word=="parent")
			{
				cin>>word;
				scanf("%d",&y);
				ans=(pos[x]==pos[y]/2);
			}
			else
			{
				cin>>word;
				scanf("%d",&y);
				ans=(pos[y]==pos[x]/2);
			}
		}
		printf(ans?"T\n":"F\n");
	}

	return 0;
}