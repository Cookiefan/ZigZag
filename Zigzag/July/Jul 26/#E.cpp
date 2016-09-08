#include <bits/stdc++.h>
#define maxn 1200
using namespace std;
typedef pair<int,int> pii;
vector<pii> ans;
int a[maxn][maxn],p[maxn][maxn];
int v[maxn];

int n,m;

//高斯消元
void gauss(int n)
{
    // for (int i=1;i<=n;i++)
    // {
    //     for (int j=1;j<=n+1;j++)
    //         cout<<a[i][j]<<' ';
    //     cout<<endl;
    // }
    int k=1;
    for (int i=1;i<=n;i++)
    {
        int p=0;
        for (int j=k;j<=n;j++)
            if (a[i][j]>0) { p=j; break;}
        if (!p) continue;
        for (int l=1;l<=n+1;l++) swap(a[p][l],a[k][l]);
        for (int j=k+1;j<=n;j++)
        {
            if (!a[j][i]) continue;
            int r=a[j][i]*a[k][i]%3;
            for (int l=1;l<=n+1;l++)
                a[j][l]=((a[j][l]-r*a[k][l])%3+3)%3;
        }
        k++;
    }
    // for (int i=1;i<=n;i++)
    // {
    //     for (int j=1;j<=n+1;j++)
    //         cout<<a[i][j]<<' ';
    //     cout<<endl;
    // }
    for (int i=n;i>0;i--)
    {
        v[i]=a[i][n+1];
        for (int j=i+1;j<=n;j++)
            v[i]=((v[i]-v[j]*a[i][j])%3+3)%3;
        v[i]=(v[i]*a[i][i])%3;
    }
}

int main()
{
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {
        memset(a,0,sizeof(a));
        memset(v,0,sizeof(v));
        
        scanf("%d%d",&n,&m);
        // for (int i=0;i<=n*m+1;i++)
        //     for (int j=0;j<=n*m+1;j++)
        //         a[i][j]=0;
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
            {
                scanf("%d",&p[i][j]);
                if (i-1>=0) a[i*m+j+1][(i-1)*m+j+1]=1;
                if (i+1<n)  a[i*m+j+1][(i+1)*m+j+1]=1;
                if (j-1>=0) a[i*m+j+1][i*m+(j-1)+1]=1;
                if (j+1<m)  a[i*m+j+1][i*m+(j+1)+1]=1;
                a[i*m+j+1][i*m+j+1]=2;
                a[i*m+j+1][n*m+1]=(3-p[i][j])%3;
            }
        gauss(n*m);
        ans.clear();
        for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
                for (int k=1;k<=v[i*m+j+1];k++)
                    ans.push_back(pii(i+1, j+1));
        int ss=ans.size();
        printf("%d\n",ss);
        for (int i=0;i<ss;i++)
            printf("%d %d\n",ans[i].first,ans[i].second);
    }

    return 0;

}