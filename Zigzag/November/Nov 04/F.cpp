#include <bits/stdc++.h>
using namespace std;
#define maxn 220
typedef double db;
int a[maxn];
int n;
db b, r, v, e, f;
db dis[maxn][maxn];
db dp[maxn];

void prepare(int st){
	db now=0, tmp=0;
	for (int i=st+1;i<=n;i++){
		while (now<a[i]-a[st]){
			if (now<r)
				tmp+=1.0/(v-f*(r-now));
			else
				tmp+=1.0/(v-e*(now-r));
			now++;
		}
		dis[st][i]=tmp;
	}
}

int main()
{
	while (scanf("%d",&n) && n){
		for (int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		scanf("%lf%lf%lf%lf%lf",&b, &r, &v, &e, &f);
		memset(dis,0,sizeof(dis));
		memset(dp, 0, sizeof(dp));
		for (int i=0;i<n;i++) prepare(i);

		dp[0]=0;
		for (int i=1;i<=n;i++){
			dp[i]=dis[0][i];
			 for (int j=1;j<i;j++)
			 	dp[i]=min(dp[i], dp[j]+b+dis[j][i]);
		}
		printf("%.5f\n", dp[n]);
	}
	return 0;
}