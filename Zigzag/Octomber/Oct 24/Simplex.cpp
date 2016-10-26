#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <math.h>
#include <limits>
#include <set>
#include <map>
using namespace std;
typedef double ld;
#define SZ 233
int n,m,t,id[SZ];
ld a[SZ][SZ],vv[SZ];
const ld eps=1e-7;
int dcmp(ld x)
{
    if(x<-eps) return -1;
    if(x>eps) return 1;
    return 0;
}
void pivot(int r,int c) //基变量r和非基变量c 
{
    swap(id[r+n],id[c]);
    ld x=-a[r][c]; a[r][c]=-1;
    for(int i=0;i<=n;i++) a[r][i]/=x;
    for(int i=0;i<=m;i++)
    {
        if(dcmp(a[i][c])&&i!=r);else continue;
        x=a[i][c]; a[i][c]=0;
        for(int j=0;j<=n;j++) a[i][j]+=x*a[r][j];
    }
}
void solve()
{
    for(int i=1;i<=n;i++) id[i]=i;
    while(1) //init
    {
        int x=0,y=0;
        double mi=0;
        for(int i=1;i<=m;i++)
            if (dcmp(a[i][0]-mi)<0){
                mi=a[x=i][0];
            // if(dcmp(a[i][0])<0) x=i; 
        }
        if(!x) break;
        for(int i=1;i<=n;i++)
            if(dcmp(a[x][i])>0) {y=i; break;}
        if(!y) {puts("Infeasible"); return;}
        pivot(x,y);
    }
    while(1) //simplex
    {
        int x=0,y=0;
        for(int i=n;i>=1;i--)
        {
            if(dcmp(a[0][i])>0) x=i; 
        }
        if(!x) break;
        double w,t; bool f=1;
        for(int i=1;i<=m;i++)
        {
            if(dcmp(a[i][x])<0&&((t=-a[i][0]/a[i][x]),f||t<w)) w=t, y=i, f=0;
        }
        if(!y) {puts("Unbounded"); return;}
        pivot(y,x);
    }
    printf("%.9lf\n",a[0][0]);
    if(!t) return;
    for(int i=1;i<=n;i++) vv[i]=0;
    for(int i=n+1;i<=n+m;i++) vv[id[i]]=a[i-n][0];
    for(int i=1;i<=n;i++) printf("%.9lf ",vv[i]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++) scanf("%lf",&a[0][i]);
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++) scanf("%lf",&a[i][j]), a[i][j]*=-1;
        scanf("%lf",&a[i][0]);
    }
    solve();
}