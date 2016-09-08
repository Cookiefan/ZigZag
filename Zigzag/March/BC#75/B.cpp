#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 12
using namespace std;
int v[maxn],a[maxn];
int mid[maxn][maxn];
int n,m;

bool judge()
{
	if (n<4) return 0;
	for (int i=1;i<=n;i++) if (a[i]<1 || a[i]>9) return 0;
	for (int i=1;i<n;i++)
		for (int j=i+1;j<=n;j++)
			if (a[i]==a[j])
				return 0;
	memset(v,0,sizeof(v));
	for (int i=1;i<n;i++)
	{
		if (mid[a[i]][a[i+1]] && !v[mid[a[i]][a[i+1]]])
			return 0;
		v[a[i]]=1;
	}
	return 1;
}

int main()
{
	memset(mid,0,sizeof(mid));
	mid[1][3]=mid[3][1]=2;
	mid[3][9]=mid[9][3]=6;
	mid[7][9]=mid[9][7]=8;
	mid[1][7]=mid[7][1]=4;
	mid[1][9]=mid[9][1]=5;
	mid[3][7]=mid[7][3]=5;
	mid[2][8]=mid[8][2]=5;
	mid[4][6]=mid[6][4]=5;
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if (judge()) printf("valid\n");
		else printf("invalid\n");
	}	
	return 0;
}