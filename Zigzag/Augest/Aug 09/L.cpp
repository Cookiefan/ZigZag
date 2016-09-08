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
struct Edge
{
    int y,i,v;
    Edge(){}
    Edge(int _y,int _i,int _v):y(_y),i(_i),v(_v){}
};
struct Point
{
    int x,y;
    Point(){}
    Point(int _x,int _y):x(_x),y(_y){}
};
bool cmp(Edge x,Edge y)
{
    if (x.y==y.y)
        return x.v<y.v;
    else return x.y<y.y;

}
Edge x[50010],y[50010];
Point p[50010];
int mx[50010],my[50010],run[50010];
queue <int> q;
int tot,now,n_x,n_y;
int main()
{
    int n;
    while (scanf("%d",&n) && n)
    {
        memset(mx,0,sizeof(mx));
        memset(my,0,sizeof(my));
        memset(run,0,sizeof(run));
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d",&p[i].x,&p[i].y);
            x[i]=Edge(p[i].x,i,p[i].x+p[i].y);
            y[i]=Edge(p[i].y,i,p[i].x+p[i].y);
        }
        sort(x+1,x+1+n,cmp);x[0].y=-1;x[n+1].y=-1;
        sort(y+1,y+1+n,cmp);y[0].y=-1;y[n+1].y=-1;
        for (int i=1;i<=n;i++)
        {
            mx[x[i].i]=i;
            my[y[i].i]=i;
        }
        tot=1;
        q.push(x[1].i);run[x[1].i]=1;
        while (!q.empty())
        {
            now=q.front();
            // cout<<now<<' '<<x[mx[now]].y<<' '<<y[my[now]].y<<endl;
            q.pop();
            n_x=mx[now];
            for (int i=n_x+1;;i++)
            {
                if (x[i].y!=x[i-1].y) break;
                if (run[x[i].i]==1) break;
                tot++;
                run[x[i].i]=1;
                q.push(x[i].i);
            }

            n_y=my[now];
            for (int i=n_y+1;;i++)
            {
                if (y[i].y!=y[i-1].y) break;
                if (run[y[i].i]==1) break;
                tot++;
                run[y[i].i]=1;
                q.push(y[i].i);
            }
        }
        // cout<<"1="<<tot<<endl;
        q.push(x[1].i);run[x[1].i]=2;
        while (!q.empty())
        {
            now=q.front();
            q.pop();
            n_x=mx[now];
            for (int i=n_x-1;;i--)
            {
                if (x[i].y!=x[i+1].y) break;
                if (run[x[i].i]==2) break;
                if (run[x[i].i]==0) tot++;
                run[x[i].i]=2;
                q.push(x[i].i);
            }

            n_y=my[now];
            for (int i=n_y+1;;i++)
            {
                if (y[i].y!=y[i-1].y) break;
                if (run[y[i].i]==2) break;
                if (run[x[i].i]==0) tot++;
                run[y[i].i]=2;
                q.push(y[i].i);
            }
        }
        if (tot==n) printf("YES\n");
        else printf("NO\n");
        // cout<<"2="<<tot<<endl;
    }    
}