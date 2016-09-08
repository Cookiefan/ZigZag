#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <bitset>
#define inf 1000000007
#define maxn 52000
#define maxm 520

using namespace std;

struct score
{
    int x,y;
    friend bool operator <(score a, score b)
    {
        return a.x<b.x;
    };
}s[6][maxn];

int n,m,p,num,block;
int bel[maxn],l[maxm],r[maxm];
int a[6][maxn];
bitset<50005> b[6][maxm];
bitset<50005> now[6];

int main()
{
    int Case;
    scanf("%d",&Case);
    for (int i=1;i<=5;i++) b[i][0].reset();
    for (int o=1;o<=Case;o++)
    {
        scanf("%d%d",&n,&m);
        for (int j=1;j<=n;j++)
            for (int i=1;i<=5;i++)    
            {
                scanf("%d",&a[i][j]);
                s[i][j].x=a[i][j];
                s[i][j].y=j;
            }
        for (int i=1;i<=5;i++)
        {
            sort(s[i]+1,s[i]+n+1);
            sort(a[i]+1,a[i]+n+1);
        }
        int block=sqrt(n);
        int num=n/block+(n%block!=0);
        for (int i=1;i<=n;i++) bel[i]=(i-1)/block+1;
        for (int i=1;i<=num;i++) l[i]=(i-1)*block+1;
        for (int i=1;i<=num;i++) r[i]=i*block;
        r[num]=n;
        for (int i=1;i<=5;i++)
            for (int j=1;j<=num;j++)
            {
                b[i][j]=b[i][j-1];
                for (int k=l[j];k<=r[j];k++)
                    b[i][j][s[i][k].y]=1;
            }
        scanf("%d",&p);
        int x[6],ans=0;
        for (int q=1;q<=p;q++)
        {
            for (int i=1;i<=5;i++) scanf("%d",&x[i]);
            for (int i=1;i<=5;i++) x[i]^=ans;
            for (int i=1;i<=5;i++) now[i].reset();
            for (int i=1;i<=5;i++)
            {
                int tmp=upper_bound(a[i]+1,a[i]+n+1,x[i])-a[i]-1;
                if (tmp==0) continue;
                now[i]=b[i][bel[tmp]-1];
                for (int j=l[bel[tmp]];j<=tmp;j++)
                    now[i][s[i][j].y]=1;
            }
            now[0]=now[1]&now[2]&now[3]&now[4]&now[5];
            ans=now[0].count();
            printf("%d\n",ans);
        }
    }
    return 0;
}