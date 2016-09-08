#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int n,m;
int ans;

int cut(int x, int y)
{
	//cout<<x<<' '<<y<<endl;
	if (x==0)
	{
		return y;
	}
	else
	{
		ans+=y/x;
		return x?cut(y%x, x):y;
	}
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		ans=0;
		scanf("%d%d",&n,&m);
		cut(n,m);
		printf("%d\n",ans);

	}

	
	return 0;
}