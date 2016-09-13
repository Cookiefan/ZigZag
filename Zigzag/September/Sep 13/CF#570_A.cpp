#include <bits/stdc++.h>
#define maxn 120
using namespace std;

int v[maxn];
int n,m;

int main(){
	scanf("%d%d",&n,&m);
	int x;
	for (int i=1;i<=m;i++)
	{
		int mx=-1, id=0;
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			if (x>mx) mx=x, id=j;
		}
		v[id]+=1;
	}
	int mx=-1, id;
	for (int i=1;i<=n;i++)
		if (v[i]>mx) mx=v[i], id=i;
	printf("%d\n", id);

	return 0;
}