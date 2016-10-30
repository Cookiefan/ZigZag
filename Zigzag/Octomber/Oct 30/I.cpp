#include <bits/stdc++.h>
using namespace std ;
#define maxn 200200
#define eps 1e-8
typedef long long LL;
LL a[maxn], f[maxn], s[maxn];
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
deque<int> q;

int n,p,num;

bool judge(int x, int y, int z){
    return (f[y]-f[x]+s[y]*s[y]-s[x]*s[x])>s[z]*2*(s[y]-s[x]);
}

bool better(int x, int y, int z){
    double t1=(double)(f[y]-f[x]+s[y]*s[y]-s[x]*s[x])/(s[y]-s[x]);
    double t2=(double)(f[z]-f[y]+s[z]*s[z]-s[y]*s[y])/(s[z]-s[y]);
    return t1<t2+eps;
}

void solve(int x, int y){
  f[y]=s[y]*s[y];
  int k=top[x];
  while (pre[k] && judge(q[pre[k]], q[k], y)) k=pre[k];
  //cout<<y<<' '<<q[k]<<' ';
  f[y]=min(f[y], f[q[k]]+(s[y]-s[q[k]])*(s[y]-s[q[k]])+p);
  ans=max(ans, f[y]);
  //cout<<"y: "<<y<<' '<<s[y]<<' '<<f[y]<<endl;
  while (pre[k] && better(q[pre[k]], q[k], y)) k=pre[k];
  pre[top[y]]=k;
}

void dfs(int x){
  vis[x]=1;
  for (int j=0;j<e[x].size();j++){ 
    int y=e[x][j].t;
    if (vis[y]) continue;
    q.push_back(y);
    top[y]=q.size()-1;
    a[y]=e[x][j].val;
    s[y]=s[x]+a[y];
    solve(x, y);
    dfs(y);
    q.pop_back();
  }
}

int main()
{
  freopen("I.in","r",stdin);
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
      q.push_back(1);
      top[1]=0;
      dfs(1);
      q.clear();
      printf("%I64d\n",ans);
  }
  return 0;
}
