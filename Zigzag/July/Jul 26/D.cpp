#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
// #include <ctime>
#define inf 999999999
#define mo 1000000007
#define LL long long 
using namespace std;
int sg1[1050][1050];
int sg3[1050][1050];
int sg4[1050][1050];
int num[20000];
int flag,t,o,n,m;
int x1[10]={0,0,1,1};
int y1[10]={0,1,0,1};

int x3[10]={0,2,1};
int y3[10]={0,1,2};
int Sg1(int x,int y)
{
    int xn,yn,tmp;
    if (sg1[x][y]>=0) return sg1[x][y];
    sg1[x][y]=0;
    for (int i=1;i<=3;i++)
    {
        xn=x+x1[i];yn=y+y1[i];
        if (xn>n || yn>m) continue;
        tmp=Sg1(xn,yn);
        if (tmp==0) sg1[x][y]=1; 
    }
    return sg1[x][y];
}

void Sg4()
{
    int x,y;
    int now=0;
    for (int i=1;i<=1000;i++)
    {
        if (num[i]) continue;
        x=i;y=i+now;
        num[x]=1;num[y]=1;
        now++;
        if (y<=1000)
        {
            sg4[1000+1-x][1000+1-y]=0;
            sg4[1000+1-y][1000+1-x]=0;
        }
    }
}
int main()
{
    int ans;
    scanf("%d",&t);
    n=1000;m=1000;
    memset(sg1,-1,sizeof(sg1));
    memset(sg4,1,sizeof(sg4));
    sg1[1000][1000]=0;ans=Sg1(1,1);
   // Sg4();
    while (t--)
    {
        scanf("%d%d%d",&o,&n,&m);
        if (o==1)
        {
            ans=sg1[1000-n+1][1000-m+1];
            if (ans) printf("B\n");
            else printf("G\n");
        }
        else if (o==2)
        {
            ans=n-m;
            if (ans) printf("B\n");
            else printf("G\n");
        }
        else if (o==3)
        {
            ans=-1;
            if (n==m && n%3==1) ans=0;
            else if (n%3==2 && m==n+1) ans=1;
            else if (n==m+1 && m%3==2) ans=1;  
            if (ans==-1) printf("D\n");
            else if (ans==1) printf("B\n");
            else if (ans==0) printf("G\n");
        }
        else if (o==4)
        {
            ans=sg4[1000-n+1][1000-m+1];
            if (ans) printf("B\n");
            else printf("G\n");    
        }
    }    
}