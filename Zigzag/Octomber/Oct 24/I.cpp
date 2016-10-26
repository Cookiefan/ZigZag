#include <bits/stdc++.h>
using namespace std;
#define maxn 6020
#define inf 999999999

int a[maxn][maxn];
int nxt[maxn], id[maxn], xx[maxn];
int p, q, n, m, num;

void change(int x,int y)//交换非基x与基y
{
    int last=-1;
    swap(id[x+m], id[y]);
    for (int i=0;i<=m;i++)
        if (a[x][i])
        {
            nxt[i]=last;
            last=i;
        }
    for (int i=0;i<=n;i++)
    {
        if (i==x||a[i][y]==0) continue;
        for (int j=last;j!=-1;j=nxt[j])
        {
            if (j==y) continue;
            a[i][j]-=a[i][y]*a[x][j];
        }
        a[i][y]=-a[i][y];
    }
}

int simplex()
{
    while (1)
    {
        int now=0;
        for (int i=1;i<=m;i++)     
            if (a[0][i]>0) { 
                now=i;
                break;
            }
        if (now==0) return -a[0][0];
        int tmp,mi=inf;
        for (int i=1;i<=n;i++)
            if (a[i][now]>0&&a[i][0]<mi)
                mi=a[i][0],tmp=i;
        change(tmp,now);
    }
}


int main()
{
    scanf("%d%d%d",&n,&p,&q);
    num=n;
    for (int i=1;i<=n;i++)
        scanf("%d",&a[0][i]);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[0][n+i]);
    m=0;
    for (int i=1;i<=n;i++){
        ++m;
        a[m][i]=1;
        a[m][n+i]=1;
        a[m][0]=1;
    }
    ++m;
    for (int i=1;i<=n;i++)
        a[m][i]=1;
    a[m][0]=p;
    ++m;
    for (int i=1;i<=n;i++)
        a[m][n+i]=1;
    a[m][0]=q;
    n=2*n;
    swap(n, m);
    // for (int i=0;i<=n;i++)
    // {
    //     for (int j=0;j<=m;j++)
    //         cout<<a[i][j]<<' ';
    //     cout<<endl;
    // }
    for (int i=1;i<=m;i++) id[i]=i;
    printf("%d\n",simplex());
    for (int i=m+1;i<=n+m;i++) xx[id[i]]=a[i-m][0];
    vector<int> q1, q2;
    for (int i=1;i<=num;i++)
        if (xx[i])
            q1.push_back(i);
    for (int i=num+1;i<=2*num;i++)
        if (xx[i])
            q2.push_back(i-num);
    for (int i=0;i<q1.size();i++)
        printf(i==q1.size()-1?"%d\n":"%d ",q1[i]);
    for (int i=0;i<q2.size();i++)
        printf(i==q2.size()-1?"%d\n":"%d ",q2[i]);


    // for (int i=0;i<=n;i++)
    // {
    //     for (int j=0;j<=m;j++)
    //         cout<<a[i][j]<<' ';
    //     cout<<endl;
    // }
    return 0;
}