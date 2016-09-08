#include <bits/stdc++.h>
using namespace std;
const int Max = 405;
const int eMax = 100000;
 
struct{
    int v, w, re, next;
}edge[eMax];
int N, F, D, n;
int ans, k, edgeHead[Max];
int que[Max], pre[Max];
bool vis[Max];
 
void addedge(int u, int v){      //  详细的EK过程见网络流EK的模板。
    edge[k].v = v;
    edge[k].w = 1;
    edge[k].next = edgeHead[u];
    edge[k].re = k+1;
    edgeHead[u] = k ++;
    edge[k].v = u;
    edge[k].w = 0;
    edge[k].next = edgeHead[v];
    edge[k].re = k-1;
    edgeHead[v] = k ++;
}
 
void make_map(){                 //  建图，要仔细弄好下标的关系。
    int i, f, d, u;
    memset(edgeHead, 0, sizeof(edgeHead));
    for(i = 1; i <= F; i ++)
        addedge(0, i);
    for(i = F+1; i <= F+N; i ++)
        addedge(i, i + N);
    for(i = F+2*N+1; i <= F+2*N+D; i ++)
        addedge(i, n);
    for(i = 1; i <= N; i ++){
        scanf("%d%d", &f, &d);
        while(f --){
            scanf("%d", &u);
            addedge(u, F+i);
        }
        while(d --){
            scanf("%d", &u);
            addedge(F+N+i, F+2*N+u);
        }
    }
}
 
bool bfs(){
    int head, tail, i, u, v;
    memset(vis, 0, sizeof(vis));
    head = tail = 1;
    que[tail ++] = 0;
    vis[0] = true;
    while(tail > head){
        u = que[head ++];
        for(i = edgeHead[u]; i != 0; i = edge[i].next){
            v = edge[i].v;
            if(!vis[v] && edge[i].w){
                pre[v] = i;
                if(v == n) return true;
                que[tail ++] = v;
                vis[v] = true;
            }
        }
    }
    return false;
}
 
void end(){       //  由于每条增广路径的值必为1，故这就不用算sum了。
    for(int u = n; u != 0; u = edge[edge[k].re].v){
        k = pre[u];
        edge[k].w -= 1;
        edge[edge[k].re].w += 1;
    }
    ans += 1;
}
 
int main(){
    while(scanf("%d%d%d", &N, &F, &D) != EOF){
        k = 1;
        n = F+2*N+D+1;
        make_map();
        ans = 0;
        while(bfs()) end();
        printf("%d\n", ans);
    }
    return 0;
}