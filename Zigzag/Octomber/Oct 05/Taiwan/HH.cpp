#include <bits/stdc++.h>
#define maxn 502
using namespace std;

typedef long long LL;

const LL oo=1e6+3;

LL f[maxn][maxn];
int n,m,p;

int main()
{
    freopen("H.in","r",stdin);
    scanf("%d%d%d",&n,&m,&p);
    memset(f, 0, sizeof(f));
    f[0][0]=1;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            for (int w='A';w<='Z';w++)
                (f[i+1][(j*p+w)%m]+=f[i][j])%=oo;
    for (int k=0;k<=8;k++)
    {
        for (int i=0;i<m;i++)
            cout<<f[1<<k][i]<<' ';
        cout<<endl;
    }
    for (int i=0;i<m;i++) cout<<f[n][i]<<' '; cout<<endl;
    LL ans=0;
    for (int i=0;i<m;i++)
    {
        LL tmp=(LL)f[n][i]*(f[n][i]-1)/2%oo;
        ans=(ans+tmp)%oo;
    }
    printf("%d\n",ans);


    return 0;
}
