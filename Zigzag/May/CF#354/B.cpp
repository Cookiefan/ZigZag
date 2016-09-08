#include <bits/stdc++.h>
#define maxn 120
using namespace std;
double a[maxn][maxn];

int n,t,ans;
void flow(int i)
{
	if (i>n) return ;
	for (int j=1;j<=i;j++)
		if (a[i][j]>=1.0)
		{
			//cout<<i<<' '<<j<<' '<<a[i][j]<<endl;
			ans++;
			a[i+1][j]+=(a[i][j]-1.0)/2.0;
			a[i+1][j+1]+=(a[i][j]-1.0)/2.0;
		}
	flow(i+1);
}


int main()
{
	ans=0;
	scanf("%d%d",&n,&t);
	memset(a,0,sizeof(a));
	a[1][1]=t;
	flow(1);
	printf("%d\n",ans);
	return 0;
}