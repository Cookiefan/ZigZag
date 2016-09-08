#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#define inf 999999999
#define mo 1000000007
#define LL long long 
using namespace std;
LL dp[1100][1100];
LL ans;
int a[1100],b[1100];
int n,m,sum;
int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        ans=0;
        for (int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for (int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for (int i=1;i<=n;i++)
        {
            sum=1;
            for (int j=1;j<=m;j++)
            {
                if (a[i]==b[j])
                {
                    dp[i][j]=(dp[i][j]+sum)%mo;
                }
                sum+=dp[i-1][j];
                ans=(ans+dp[i][j])%mo;
            }
        }
        printf("%I64d\n",ans);
    }
}