#include <bits/stdc++.h>
using namespace std;

#define lc (o<<1)
#define rc (o<<1|1)
#define lson lc, lft, mid
#define rson rc, mid+1, rht
#define MID(L, R) ((L)+(R)>>1)

const int MAXN = 1e5 + 10;
const int root = 1;

int N;

int from[MAXN], nxt[MAXN<<1], to[MAXN<<1], edge_siz;
void AddEdge(int u, int v) {
    to[++edge_siz] = u;
    nxt[edge_siz] = from[v];
    from[v] = edge_siz;
}

int father[MAXN], son[MAXN], dep[MAXN], siz[MAXN];
void DFS(int o, int f, int d) {
    father[o] = f; son[o] = 0;
    dep[o] = d; siz[o] = 1;

    for(int u=from[o]; u; u=nxt[u]) {
        int v = to[u];
        if( v == f ) continue;

        DFS(v, o, d+1);
        siz[o] += siz[v];
        if( siz[son[o]] < siz[v] ) son[o] = v;
    }
}

int top[MAXN], st[MAXN], ed[MAXN], id[MAXN], dfs_clock;
void DFS(int o, int t) {
    st[o] = ++dfs_clock;
    id[dfs_clock] = o;
    top[o] = t;

    if( son[o] ) {
        DFS(son[o], t);
        for(int u=from[o]; u; u=nxt[u]) {
            int v = to[u];
            if( v != father[o] and v != son[o] )
                DFS(v, v);
        }
    }

    ed[o] = dfs_clock;
}

int LCA(int u, int v) {
    while( top[u] != top[v] ) {
        if( dep[top[u]] < dep[top[v]] ) swap(u, v);
        u = father[top[u]];
    }
    return dep[u] < dep[v]? u: v;
}

pair<int, int> T[MAXN<<2];
int color[MAXN];

void Pushdown(int o) {
    T[lc].first += T[o].first;
    T[rc].first += T[o].first;
    T[o].first = 0;
}

void Build(int o, int lft, int rht) {
    T[o].first = 0;
    if( lft == rht ) {
        T[o].second = color[id[lft]];
    } else {
        int mid = MID(lft, rht);
        Build(lson);
        Build(rson);

        T[o].second = 1;
    }
}

void Update(int o, int lft, int rht, int L, int R, int V) {
    if( L <= lft and rht <= R ) {
        T[o].first += V;
    } else {
        int mid = MID(lft, rht);
        if( L <= mid ) Update(lson, L, R, V);
        if( R > mid ) Update(rson, L, R, V);
    }
}

int Query(int o, int lft, int rht, int P) {
    if( lft == rht ) return T[o].first;
    if( T[o].first ) Pushdown(o);

    int mid = MID(lft, rht);
    if( P <= mid ) return Query(lson, P);
    return Query(rson, P);
}

void UpdatePath(int u, int v, int w) {
    while( top[u] != top[v] ) {
        if( dep[top[u]] < dep[top[v]] ) swap(u, v);
        Update(1, 1, N, st[top[u]], st[u], w);
        u = father[top[u]];
    }
    if( dep[u] > dep[v] ) swap(u, v);
    Update(1, 1, N, st[u], st[v], w);
}

set<int> s[MAXN];
set<int>:: iterator it;

int LowColor(int o, int lft, int rht, int L, int R) {
    if( !T[o].second ) return 0;
    if( lft == rht ) return T[o].second;

    int mid = MID(lft, rht);
    int rcolor = 0;
    if( R > mid ) rcolor = LowColor(rson, L, R);
    return (!rcolor and L <= mid )? LowColor(lson, L, R): rcolor;
}

int TheColor(int x) {
    while( top[x] != top[root] ) {
        int ret = LowColor(1, 1, N, st[top[x]], st[x]);
        if( ret ) return ret;
        x = father[top[x]];
    }
    return LowColor(1, 1, N, st[root], st[x]);
}

void Maintain(int x, int c, int op) {
    if( ~op ) s[c].insert(st[x]);
    it = upper_bound(s[c].begin(), s[c].end(), st[x]);
    int pr = 0, su = 0;

    if( it != s[c].end() ) {
        su = LCA(x, id[*it]);
    }
    --it;
    if( it != s[c].begin() ) {
        --it;
        pr = LCA(x, id[*it]);
    }

    if( !pr and !su ) UpdatePath(1, x, op);
    else {
        if( st[pr] < st[su] ) pr = su;

        UpdatePath(pr, x, op);
        UpdatePath(pr, pr, -op);
    }

    if( op == -1 ) s[c].erase(st[x]);
}

void Remove(int o, int lft, int rht, int L, int R) {
    if( !T[o].second ) return;
    if( lft == rht ) {
        Maintain(id[lft], T[o].second, -1);
        T[o].second = 0;
    } else {
        int mid = MID(lft, rht);
        if( L <= mid ) Remove(lson, L, R);
        if( R > mid ) Remove(rson, L, R);

        T[o].second = T[lc].second or T[rc].second;
    }
}

void Insert(int o, int lft, int rht, int P, int C) {
    if( lft == rht ) {
        Maintain(id[lft], C, 1);
        T[o].second = C;
    } else {
        int mid = MID(lft, rht);
        if( P <= mid ) Insert(lson, P, C);
        else Insert(rson, P, C);

        T[o].second = 1;
    }
}

void Init() {
    memset(from, 0, sizeof from);
    edge_siz = 0;

    for(int i=1; i <= N; ++i) s[i].clear();
    dfs_clock = 0;
}

void work() {
    int T_T, Q, u, v, w, cmd;

    scanf("%d", &T_T);
    for(int kase = 1; kase <= T_T; ++kase) {
        printf("Case #%d:\n", kase);

        scanf("%d", &N); Init();
        for(int i=1; i < N; ++i) {
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
            AddEdge(v, u);
        }
        for(int i=1; i <= N; ++i) scanf("%d", color+i);

        DFS(root, -1, root);
        DFS(root, 1);
        Build(1, 1, N);

        for(int i=1; i <= N; ++i) Maintain(i, color[i], 1);

        scanf("%d", &Q);
        while( Q-- ) {
            scanf("%d", &cmd);
            switch( cmd ) {
                case 0:
                    scanf("%d%d", &u, &v);
                    Remove(1, 1, N, st[u], ed[u]);
                    Insert(1, 1, N, st[u], v);
                    break;
                case 1:
                    scanf("%d", &u);
                    int flag = 0;
                    int c = TheColor(u);
                    if( c ) {
                        it = lower_bound(s[c].begin(), s[c].end(), st[u]);
                        if( it == s[c].end() || *it > ed[u] ) flag = 1;
                    }
                    printf("%d\n", Query(1, 1, N, st[u])+flag);
                    break;
            }

        }
    }
}

int main()
{
    work();
    return 0;
}