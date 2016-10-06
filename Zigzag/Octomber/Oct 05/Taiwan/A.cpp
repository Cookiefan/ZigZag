#include <bits/stdc++.h>
#define maxn 200200
#define low 30
using namespace std;
int f[4][maxn];
int fa[maxn][33];
int py[maxn];
int a[maxn];
int n, m;
char s[maxn];

int main()
{
    //freopen("A.in","r",stdin);
    scanf(" %s",s);
    n=strlen(s);
    for (int i=0;i<n;i++)
        if (s[i]=='e') a[i+1]=0;
        else if (s[i]=='a') a[i+1]=1;
        else if (s[i]=='s') a[i+1]=2;
        else a[i+1]=3;
    memset(f, 0, sizeof(f));
    for (int i=1;i<=n;i++)
        if (a[i]==0)
            f[0][i]=i;
        else
            f[0][i]=f[0][i-1];

    for (int k=1;k<=3;k++)
        for (int i=1;i<=n;i++)
            if (a[i]==k)
                f[k][i]=f[k-1][i];
            else
                f[k][i]=f[k][i-1];

    memset(py, 0, sizeof(py));
    for (int i=1;i<=n;i++)
        if (a[i]==3)
            py[i]=i;
        else
            py[i]=py[i-1];

    for (int i=1;i<=n;i++)
        if (a[i]==3)
            fa[i][0]=f[3][i];

    //for (int i=1;i<=n;i++) cout<<fa[i][0]<<' '; cout<<endl;

    for (int k=1;k<low;k++)
        for (int i=1;i<=n;i++)
            fa[i][k]=fa[py[fa[i][k-1]]][k-1];

    scanf("%d",&m);
    int x, y;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        y=py[y];
        if (y<x) printf("0\n");
        else{
            int ans=0;
            for (int k=low;k>=0;k--)
                if (x<=fa[y][k])
                {
                    ans+=(1<<k);
                    y=py[fa[y][k]];
                }
            printf("%d\n", ans);
        }
    }
    return 0;
}

