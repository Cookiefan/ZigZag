#include <bits/stdc++.h>
#define LL long long
template <class T>
inline void rd(T &x) { char c = getchar(); x = 0;while(!isdigit(c)) c = getchar();
while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }}
template <class T> void Out(T a) { if(a < 0){putchar('-');a = -a;}if(a >= 10)Out(a / 10);putchar(a % 10 + '0');  }
using namespace std;
const int N=200500;
queue <int> q[3];
int dis[N],head[N],sum[N],in[N];
int l;
int n,m,s;
struct Point
{
    int y,next;
    Point(){}
    Point(int _y,int _next){y=_y;next=_next;}

}edge[N];

void Addedge(int x,int y)
{
    l++;
    edge[l]=Point(y,head[x]);head[x]=l;

    l++;
    edge[l]=Point(x,head[y]);head[y]=l;

    return ;
}

void Pre()
{
    memset(dis,-1,sizeof(dis));
    memset(sum,0,sizeof(sum));
    memset(in,0,sizeof(in));
    memset(head,0,sizeof(head));
    l=1;
    while (!q[1].empty()) q[1].pop();
    while (!q[0].empty()) q[0].pop();

    for (int i=1;i<=n;i++)
        q[1].push(i);
    sum[0]=1;
}

void Dfs(int fl,int now)
{
    int a,b,tmp,x,y;
    a=fl;b=fl^1;
    dis[s]=0;
    while (!q[a].empty())
    {
        tmp=0;
        x=q[a].front();
        q[a].pop();
        if (x==s) continue;
        for (int i=head[x];i;i=edge[i].next)
        {
            y=edge[i].y;
//            cout<<x<<' '<<y<<' '<<dis[y]<<' '<<now<<endl;
            if (dis[y]==now) tmp++;
        }
//        cout<<x<<' '<<tmp<<' '<<sum[now]<<endl;
        if (tmp==sum[now])
        {
            if (in[x]!=n-1) q[b].push(x);
        }
        else
        {
            dis[x]=now+1;
            sum[now+1]++;
        }
    }
    if (!q[b].empty()) Dfs(b,now+1);
    return ;
}

int main()
{
    int t,x,y,fl;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        Pre();
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            in[x]++;
            in[y]++;
            Addedge(x,y);
        }

        scanf("%d",&s);

        if (in[s]==n-1)
        {
            for (int i=1;i<=n;i++)
            {
                if (i!=s) printf("%d\n",dis[i]);
            }
            continue ;
        }

        Dfs(1,0);

        for (int i=1;i<=n;i++)
        {
            if (i!=s) printf("%d\n",dis[i]);
        }
    }
    return 0;
}
