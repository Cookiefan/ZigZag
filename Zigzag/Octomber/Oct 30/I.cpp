#include <bits/stdc++.h>
using namespace std ;
#define maxn 100200
typedef long long LL;
LL f[maxn], s[maxn];
LL ans;
struct edge{
  int s, t, val;
  edge(){}
  edge(int x,int y,int z):
    s(x),t(y),val(z){}
};
vector<edge> e[maxn];
int vis[maxn];
int top[maxn], pre[maxn];
int q[maxn];
int n,p,num;

bool judge(int x, int y, int z){
    return (f[y]-f[x]+s[y]*s[y]-s[x]*s[x])>s[z]*2*(s[y]-s[x]);
}

bool better(int x, int y, int z){
    LL t1=(f[y]-f[x]+s[y]*s[y]-s[x]*s[x])*(s[z]-s[y]);
    LL t2=(f[z]-f[y]+s[z]*s[z]-s[y]*s[y])*(s[y]-s[x]);
    return t1>=t2;
}

void solve(int x, int y){
  f[y]=s[y]*s[y];
  int k=top[x];
  while (k && judge(q[pre[k]], q[k], y)) k=pre[k];

  f[y]=min(f[y], f[q[k]]+(s[y]-s[q[k]])*(s[y]-s[q[k]])+p);
  ans=max(ans, f[y]);

  k=top[x];
  while (k && better(q[pre[k]], q[k], y)) k=pre[k];
  pre[top[y]]=k;
}

void dfs(int x){
  vis[x]=1;
  for (int j=0;j<e[x].size();j++){ 
    int y=e[x][j].t;
    if (vis[y]) continue;
    q[top[y]=++num]=y;
    s[y]=s[x]+e[x][j].val;
    solve(x, y);
    dfs(y);
    num--;
  }
}

int main()
{
  //freopen("I.in","r",stdin);
  int Case;
  scanf("%d",&Case);
  for (int o=1;o<=Case;o++){
      scanf("%d%d",&n,&p);
      int x,y,z;
      for (int i=1;i<=n;i++) e[i].clear();
      for (int i=1;i<n;i++){
          scanf("%d%d%d",&x,&y,&z);
          e[x].push_back(edge(x,y,z));
          e[y].push_back(edge(y,x,z));
      }
      memset(vis,0,sizeof(vis));
      ans=0;
      s[1]=0; f[1]=0;
      q[top[1]=num=0]=1;
      dfs(1);
      printf("%I64d\n",ans);
  }
  return 0;
}
