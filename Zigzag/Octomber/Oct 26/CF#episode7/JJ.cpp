#include <bits/stdc++.h>
using namespace std;
#define maxn 100200
typedef long long LL;
#define inf 9999999999999999ll

int num;
LL sum[maxn], key[maxn], lmx[maxn], rmx[maxn], smx[maxn];
int fa[maxn], c[maxn][2], rev[maxn];

LL max(LL a, LL b, LL c){
    return max(a, max(b, c));
}

LL max(LL a, LL b, LL c, LL d, LL e, LL f){
    return max(max(a, b, c), max(d, e, f));
}

void update(int x){
    sum[x]=sum[c[x][0]]+sum[c[x][1]]+key[x];

    smx[x]=max(key[x], smx[c[x][0]], smx[c[x][1]], 
               rmx[c[x][0]]+key[x], key[x]+lmx[c[x][1]], 
               rmx[c[x][0]]+key[x]+lmx[c[x][1]]);

    lmx[x]=max(lmx[c[x][0]],
               sum[c[x][0]]+key[x],
               sum[c[x][0]]+key[x]+lmx[c[x][1]]);

    rmx[x]=max(rmx[c[x][1]],
               sum[c[x][1]]+key[x],
               sum[c[x][1]]+key[x]+rmx[c[x][0]]);
}

void reverse(int x){
    if (!x) return ;
    swap(c[x][0], c[x][1]);
    swap(lmx[x], rmx[x]);
    rev[x]^=1;
}

void down(int x){
    if (rev[x]){
        reverse(c[x][0]);
        reverse(c[x][1]);
        rev[x]=0;
    }
}

bool is_root(int x){
    return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}

void relax(int x){
    if (!is_root(x)) relax(fa[x]);
    down(x);
}

void zigzag(int x){
    int y=fa[x], z=fa[y];
    int p=(c[y][1]==x), q=p^1;
    if (!is_root(y)) c[z][c[z][0]!=y]=x;
    fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
    c[y][p]=c[x][q]; c[x][q]=y;
    update(y);
}
void splay(int x){
    relax(x);
    while (!is_root(x)){
        int y=fa[x], z=fa[y];
        if (!is_root(y))
            ((c[y][0]==x)^(c[z][0]==y))
            ?zigzag(x):zigzag(y);
        zigzag(x);
    }
    update(x);
}
int access(int x){
    int y=0;
    for (;x;y=x, x=fa[x]){
        splay(x);
        c[x][1]=y;
        update(x);
    }
    return y;
}

void make_root(int x){
    access(x);
    splay(x);
    reverse(x);
}

void split(int x, int y){
    make_root(y);
    access(x);
    splay(x);
}

void link(int x, int y)
{
    make_root(x);
    fa[x]=y;
}

vector<int> t[maxn];

void dfs(int x){
    for (int j=0;j<t[x].size();j++){
        int y=t[x][j];
        if (y!=fa[x]){
            //fa[y]=x;
            link(y,x);
            dfs(y);
        }
    }
}
    
int n, m;
void show(){
    for (int i=1;i<=n;i++)
        cout<<"i: "<<i<<' '<<fa[i]<<' '<<c[i][0]<<' '<<c[i][1]<<' '<<sum[i]<<' '<<lmx[i]<<' '<<rmx[i]<<' '<<smx[i]<<endl;
}

int main()
{
    //freopen("J.in","r",stdin);
    scanf("%d",&n);
    int x,y ;
    for (int i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        t[x].push_back(y);
        t[y].push_back(x);
        link(x,y);
    }
    key[0]=sum[0]=rev[0]=0;
    lmx[0]=rmx[0]=smx[0]=-inf;
    for (int i=1;i<=n;i++){
        scanf("%I64d",&key[i]);
        rev[i]=0;
        sum[i]=lmx[i]=rmx[i]=smx[i]=key[i];
    }
    //dfs(1);
    scanf("%d",&m);
    for (int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        split(x,y);
        LL ans=max(lmx[x], smx[x], rmx[x]);
        // access(x);
        // int lca=access(y);

        // splay(x);
        // LL ans=-inf;
        // ans=max(key[lca], smx[c[lca][1]], key[lca]+lmx[c[lca][1]]);
        // if (x!=lca)
        //     ans=max(ans, max(smx[x], lmx[x]+key[lca], lmx[x]+key[lca]+lmx[c[lca][1]]));
        printf("%I64d\n",ans);
    }
    return 0;
}