#include <bits/stdc++.h>  
using namespace std;  
  
const int maxn =100000 + 100;  
vector<int>g[maxn];  
int n;  
  
void init()  
{  
    scanf("%d", &n);  
    for (int i = 0; i <= n; ++ i)  
    {  
        g[i].clear();  
    }  
    for (int i = 1; i <= n; ++ i)  
    {  
        int s, t;  
        scanf("%d%d", &s, &t);  
        g[s].push_back(t);  
        g[t].push_back(s);  
    }  
}  
  
const int maxnode = 6*maxn;  
  
struct node  
{  
    int lson, rson;  
    int val;//区间权重  
    int change;//区间修改值,为0表示没有需要传递的  
}tree[maxnode];  
int tail;  
  
  
char input[20];  
int du[maxn];  
queue<int>q;  
int dfn[maxn], dfncnt;  
bool vis[maxn];  
  
vector<int>root[maxn];//作为根的节点的朋友节点  
  
  
void bfs(int arg)  
{  
    //du[i]==2表示为一个root  
  
    //root[arg]可以知道arg作为根的时候，和哪些点直接连接  
    root[arg].clear();  
    for (auto will : g[arg])  
        if (du[will] == 2)  
            root[arg].push_back(will);  
  
  
    //vis数组，是为了避免找儿子的时候，找到父亲了  
    vis[arg] = true;  
    q.push(arg);  
    while (!q.empty())  
    {  
        int now = q.front();  
        q.pop();  
        dfn[now] = ++dfncnt;  
        for (auto will : g[now])  
        {  
            if (du[will] == 2)  continue;  
            if (vis[will])  continue;  
            q.push(will);  
            vis[will] = true;  
        }  
    }  
}  
  
int minson[maxn], maxson[maxn];//最小最大的儿子编号  
int mingrandson[maxn], maxgrandson[maxn];//最小最大的孙子编号  
int pre[maxn];//父节点  
  
//dfs是找出自己儿子层的数字，和孙子层的数字  
void dfs(int now, int fa)  
{  
    pre[now]=fa;  
    minson[now] = mingrandson[now] = 0x7fffffff;  
    maxson[now] = maxgrandson[now] = -1;  
    for (auto will : g[now])  
    {  
        if (will == fa) continue;  
        if (du[will] == 2)  continue;  
        dfs(will, now);  
        if (dfn[will] > maxson[now]) maxson[now] = dfn[will];  
        if (dfn[will] < minson[now]) minson[now] = dfn[will];  
        if (minson[will] < mingrandson[now]) mingrandson[now] = minson[will];  
        if (maxson[will] > maxgrandson[now]) maxgrandson[now] = maxson[will];  
    }  
}  
  
//#define pr(x) cout<<#x<<" = "<<x<<" "  
//#define prln(x)   cout<<#x<<" = "<<x<<endl  
#define pr(x)   x  
#define prln(x) x  
  
void predoit()  
{  
    memset(du,0,sizeof(du));  
    memset(pre,-1,sizeof(pre));  
    for (int i = 1; i <= n; ++ i)  
    {  
        du[i] = g[i].size();  
        if (du[i] == 1)   
        {  
            //prln(i);  
            q.push(i);  
        }  
    }  
  
    while (!q.empty())  
    {  
        int now = q.front();  
        q.pop();  
        for (auto will : g[now])  
        {  
            du[will]--;  
            if (du[will] == 1)  
            {  
                q.push(will);  
            }  
        }  
    }  
    //for (int i = 1; i <= n; ++ i)  
    //if (du[i] == 2)   prln(i);  
  
    memset(vis, 0, sizeof(vis));//访问标记  
    memset(dfn, 0, sizeof(dfn));//BFS时间戳  
    dfncnt = 0;//BFS时间戳记录器  
  
    for (int i = 1; i <= n; ++ i)  
        if (du[i] == 2)  
        {  
            bfs(i);  
            dfs(i, -1);  
        }  
    for (int i = 1; i <= n;++i)  
        pr(i),prln(dfn[i]);  
}  
  
int ql, qr, qans;  
#define LSON tree[o].lson,L, M  
#define RSON tree[o].rson, M + 1 , R  
#define SELF o,L,R  
#define lc tree[o].lson  
#define rc tree[o].rson  
  
void build(int o, int L, int R)  
{  
    tree[o].change = 0;  
    tree[o].val = 0;  
    if (L== R)  
    {  
        tree[o].val = 0;  
        return ;  
    }  
    tree[o].lson = ++ tail;  
    tree[o].rson = ++ tail;  
    int M = L + (R - L) / 2;  
    build(LSON);  
    build(RSON);  
}  
  
void push_down(int o, int L, int R)//向下传递标记  
{  
    if (tree[o].change && L < R)  
    {  
        tree[o].val += tree[o].change * (R-L+1);  
        tree[lc].change += tree[o].change;  
        tree[rc].change += tree[o].change;  
        tree[o].change = 0;  
    }  
}  
  
void maintain(int o, int L, int R)//把o的儿子的信息，归到o节点  
{  
    //此题不需要  
    push_down(SELF);  
    if (L < R)  
    {  
        int M = L+(R-L)/2;  
        tree[o].val = tree[lc].val + tree[rc].val + tree[lc].change * (M-L+1) + tree[rc].change * (R-M);  
    }  
}  
  
int query(int o, int L, int R)  
{  
    if (ql <= L && R <= qr)  
    {  
        return tree[o].val + tree[o].change * (R-L+1);//因为根节点的传递标记一直都在  
    }  
    push_down(SELF);  
    int M = L + (R - L) / 2;  
    int ret = 0;  
    if (ql <= M) ret += query(LSON);  
    else maintain(LSON);  
    if (qr > M)  ret += query(RSON);  
    else maintain(RSON);  
    maintain(SELF);  
    return ret;  
}  
  
void update(int o, int L, int R)  
{  
    if (ql <= L && R <= qr)  
    {  
        tree[o].change += qans;  
        return;  
    }else  
    {  
        push_down(SELF);  
        int M = L + (R-L)/2;  
        if (ql <= M) update(LSON);  
        else maintain(LSON);  
        if (qr > M)  update(RSON);  
        else maintain(RSON);  
    }  
    maintain(SELF);  
}  
  
vector<int>sb;  
  
void UD(int u, int k, int d)  
{  
    //一会儿赋值下QU，然后略改一下参数即可  
    qans=d;  
    if (!k)  
    {  
        ql = dfn[u], qr = dfn[u];  
        update(0, 1, n);  
        pr(ql),prln(qr);  
    }  
    else if (k==1)  
    {  
        ql = minson[u], qr = maxson[u];  
  
        update(0, 1, n);  
        pr(ql),prln(qr);  
  
        if (du[u]!=2)//u非根  
        {  
            ql = qr = dfn[pre[u]];  
            update(0, 1, n);  
            pr(ql),prln(qr);  
  
            ql = qr = dfn[u];  
            update(0, 1, n);  
            pr(ql),prln(qr);  
        }else  
        {  
            //u为根  
            for (auto will : root[u])  
            {  
                ql = qr = dfn[will];  
                update(0, 1, n);  
                pr(ql),prln(qr);  
            }  
            ql = qr = dfn[u];  
            update(0, 1, n);  
            pr(ql),prln(qr);  
        }  
    }  
    else//也就是k==2  
    {  
        ql = minson[u], qr = maxson[u];  
        update(0, 1, n);  
        pr(ql),prln(qr);  
  
        ql = mingrandson[u], qr = maxgrandson[u];  
        update(0, 1, n);  
        pr(ql),prln(qr);  
        if (du[u]!=2)  
        {  
            int fa = pre[u];  
            ql = minson[fa], qr = maxson[fa];  
            update(0, 1, n);  
            pr(ql),prln(qr);  
  
            ql = dfn[fa], qr = dfn[fa];  
            update(0, 1, n);  
            pr(ql),prln(qr);  
  
  
            if (du[fa] != 2)//依旧没到环上  
            {  
                fa = pre[fa];  
                ql = dfn[fa], qr = dfn[fa];  
                update(0, 1, n);  
                pr(ql),prln(qr);  
            }  
            else  
            {  
                for (auto will : root[fa])  
                {  
                    ql = qr = dfn[will];  
                    update(0, 1, n);  
                    pr(ql),prln(qr);  
                }  
            }  
        }  
        else  
        {  
            sb.clear();  
            for (auto will : root[u])  
            {  
                sb.push_back(will);  
  
                ql = minson[will], qr = maxson[will];  
                update(0, 1, n);  
                pr(ql),prln(qr);  
                for (auto x : root[will])  
                    sb.push_back(x);  
            }  
            sort(sb.begin(), sb.end());  
            sb.erase(unique(sb.begin(),sb.end()),sb.end());  
            for (auto will : sb)  
            {  
                ql = qr = dfn[will];  
                update(0, 1, n);  
                pr(ql),prln(qr);  
            }  
        }  
    }  
}  
  
void QU(int u, int k)  
{  
    //一会儿赋值下QU，然后略改一下参数即可  
    int sum = 0;  
    if (!k)  
    {  
        ql = dfn[u], qr = dfn[u];  
        sum += query(0, 1, n);  
        pr(ql),prln(qr);  
    }  
    else if (k==1)  
    {  
        ql = minson[u], qr = maxson[u];  
  
        sum += query(0, 1, n);  
        pr(ql),prln(qr);  
  
        if (du[u]!=2)//u非根  
        {  
            ql = qr = dfn[pre[u]];  
            sum += query(0, 1, n);  
            pr(ql),prln(qr);  
  
            ql= qr = dfn[u];  
            sum += query(0, 1, n);  
            pr(ql),prln(qr);  
  
  
        }else  
        {  
            //u为根  
            for (auto will : root[u])  
            {  
                ql = qr = dfn[will];  
                sum += query(0, 1, n);  
                pr(ql),prln(qr);  
            }  
            ql = qr = dfn[u];  
            sum += query(0, 1, n);  
            pr(ql),prln(qr);  
        }  
    }  
    else//也就是k==2  
    {  
        ql = minson[u], qr = maxson[u];  
        sum += query(0, 1, n);  
        pr(ql),prln(qr);  
  
        ql = mingrandson[u], qr = maxgrandson[u];  
        sum += query(0, 1, n);  
        pr(ql),prln(qr);  
        if (du[u]!=2)  
        {  
            int fa = pre[u];  
            ql = minson[fa], qr = maxson[fa];  
            sum += query(0, 1, n);  
            pr(ql),prln(qr);  
  
            ql = dfn[fa], qr = dfn[fa];  
            sum += query(0, 1, n);  
            pr(ql),prln(qr);  
  
  
            if (du[fa] != 2)//依旧没到环上  
            {  
                fa = pre[fa];  
                ql = dfn[fa], qr = dfn[fa];  
                sum += query(0, 1, n);  
                pr(ql),prln(qr);  
            }  
            else  
            {  
                for (auto will : root[fa])  
                {  
                    ql = qr = dfn[will];  
                    sum += query(0, 1, n);  
                    pr(ql),prln(qr);  
                }  
            }  
        }  
        else  
        {  
            sb.clear();  
            for (auto will : root[u])  
            {  
                sb.push_back(will);  
  
                ql = minson[will], qr = maxson[will];  
                sum += query(0, 1, n);  
                pr(ql),prln(qr);  
                for (auto x : root[will])  
                    sb.push_back(x);  
            }  
            sort(sb.begin(), sb.end());  
            sb.erase(unique(sb.begin(),sb.end()),sb.end());  
            for (auto will : sb)  
            {  
                ql = qr = dfn[will];  
                sum += query(0, 1, n);  
                pr(ql),prln(qr);  
            }  
        }  
    }  
    printf("%d\n", sum);  
}  
  
void doit()  
{  
    int T;  
    int u, k, d;  
    tail=0;  
    //root为0  
    build(0,1,n);  
    //for (int o = 0; o <= tail; ++ o)  
    //pr(lc),pr(rc),pr(tree[o].val),prln(tree[o].change);  
  
    scanf("%d", &T);  
    while (T--)  
    {  
        scanf("%s", input);  
        if (input[0]=='M')  
        {  
            scanf("%d%d%d", &u, &k, &d);  
            UD(u,k,d);  
            for (int o = 0; o <= tail; ++ o)  
            pr(o),pr(lc),pr(rc),pr(tree[o].val),prln(tree[o].change);  
            prln("\n\n"),prln("\n\n");  
        }else  
        {  
            scanf("%d%d", &u, &k);  
            QU(u, k);  
            for (int o = 0; o <= tail; ++ o)  
            pr(o),pr(lc),pr(rc),pr(tree[o].val),prln(tree[o].change);  
            prln("\n\n"),prln("\n\n");  
        }  
    }  
}  
  
int main()  
{  
    freopen("Q.in","r",stdin);
    freopen("Q.ans","w",stdout);
    int T;  
    scanf("%d", &T);  
    while (T--)  
    {  
        init();  
        predoit();  
        for (int i = 1; i <= n; ++ i)  
            pr(minson[i]),pr(maxson[i]),pr(mingrandson[i]),prln(maxgrandson[i]);  
        doit();  
        //break;//暂且只测一组数据  
    }  
    return 0;  
}  