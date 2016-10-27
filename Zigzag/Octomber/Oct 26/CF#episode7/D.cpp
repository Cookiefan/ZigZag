#include <bits/stdc++.h>
using namespace std;
#define maxn 50020

struct point{
    int x, y, bl, id, tp;
    point(){}
    point(int _x,int _y,int _bl,int _id,int _tp):
    x(_x),y(_y),bl(_bl),id(_id),tp(_tp){}
    bool operator <(const point &b)const{
        if (bl==b.bl)
            return y<b.y;
        else
            return bl<b.bl;
    }
};
typedef long long LL;
vector<point> q;
int a[maxn];
LL ans[maxn], sum[2][maxn];
int n, m;

LL delta(int u, int v, int x, int y){
    LL tmp=0;
    if (u<x){
        for (int i=u+1;i<=x;i++){
            tmp+=sum[1][a[i]];
            sum[0][a[i]]++;
        }
    }
    else if (x<u){
        for (int i=x+1;i<=u;i++){
            tmp-=sum[1][a[i]];
            sum[0][a[i]]--;
        }
    }
    if (v<y){
        for (int i=v+1;i<=y;i++){
            tmp+=sum[0][a[i]];
            sum[1][a[i]]++;
        }
    }
    else if (y<v){
        for (int i=y+1;i<=v;i++){
            tmp-=sum[0][a[i]];
            sum[1][a[i]]--;
        }
    }
    return tmp;
}

int main()
{
    //freopen("D.in","r",stdin);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    int u, v, x, y;
    int r=sqrt(n)+1;
    for (int i=1;i<=m;i++){
        scanf("%d%d%d%d",&u,&x,&v,&y);
        q.push_back(point(x, y, x/r, i, 1));
        q.push_back(point(x, v-1, x/r, i, -1));
        q.push_back(point(u-1, y, (u-1)/r, i, -1));
        q.push_back(point(u-1, v-1, (u-1)/r, i, 1));
    }
    sort(q.begin(), q.end());
    int xx=0, yy=0;
    LL now=0;
    for (int i=0;i<q.size();i++){
        point qu=q[i];
        //cout<<qu.id<<' '<<qu.x<<' '<<qu.y<<' '<<qu.tp<<endl;
        now=now+delta(xx,yy,qu.x,qu.y);
        //cout<<now<<endl;
        xx=qu.x; yy=qu.y;
        ans[qu.id]+=(LL)now*qu.tp;
    }
    for (int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);

    return 0;
}