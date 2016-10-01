#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cctype>
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;
const int max_dis = 1e9;

struct Edge{
    int to;
    int dis;
    Edge(int to,int dis){
        this -> to = to;
        this -> dis = dis;
    }
};

struct Node{
    int d;
    int v;
    int pose;    // 0 代表最短路   1 代表次短路
    friend bool operator<(Node x,Node y){
        if(x.d==y.d) return x.v>y.v;
        return x.d>y.d;
    }
};

int N,M,S,E,a,b,c;
bool vis[maxn][2];
int dist[maxn][2];
int degree[maxn][2];
vector<Edge>G[maxn];

void dij(int s,int e){

    for(int i=0;i<maxn;i++){
        dist[i][0]=dist[i][1]=max_dis;
        degree[i][0]=degree[i][1]=0;
        vis[i][0]=vis[i][1]=false;
    }
    priority_queue<Node>q;
    while(q.size()) q.pop();
    Node p,w;
    p.d=0; p.v=s; p.pose=0;
    degree[p.v][p.pose]=1;
    q.push(p);
    while(q.size()){
        p=q.top(); q.pop();
        if(vis[p.v][p.pose]) continue;
        vis[p.v][p.pose]=true;
        for(int i=0;i<G[p.v].size();i++){

            Edge& e=G[p.v][i];
            if(!vis[e.to][0]&&p.d+e.dis<dist[e.to][0]){  //找到一条比当前最短路更短的路
                if(dist[e.to][0]!=max_dis){              //作为次短路，入队
                    w.v=e.to; w.d=dist[e.to][0]; w.pose=1;
                    dist[e.to][1]=dist[e.to][0];
                    degree[e.to][1]=degree[e.to][0];
                    q.push(w);
                }
                w.v=e.to; w.d=p.d+e.dis; w.pose=0;       //更新最短路，入队
                dist[e.to][0]=w.d; degree[e.to][0]=degree[p.v][p.pose];
                q.push(w);
            }

            else if(!vis[e.to][0]&&p.d+e.dis==dist[e.to][0]){ //找到一条相同距离的最短路，更新条数，不入队
                degree[e.to][0]+=degree[p.v][p.pose];
            }

            else if(!vis[e.to][1]&&p.d+e.dis<dist[e.to][1]){ //找到一条比当前次短路更短的路，不可以更新最短路，可更新次短路，入队
                w.v=e.to; w.d=p.d+e.dis; w.pose=1;
                dist[e.to][1]=w.d; degree[e.to][1]=degree[p.v][p.pose];
                q.push(w);
            }

            else if(!vis[e.to][1]&&p.d+e.dis==dist[e.to][1]){ //找到一条相同距离的次短路，更新条数，不入队
                degree[e.to][1]+=degree[p.v][p.pose];
            }
        }
    }
}

int main(){
    while(scanf("%d%d%d%d",&N,&M,&S,&E)!=EOF){
        for(int i=0;i<maxn;i++) G[i].clear();
        for(int i=0;i<M;i++){
            scanf("%d%d%d",&a,&b,&c);
            G[a].push_back(Edge(b,c));
        }
        dij(S,E);
        printf("%d %d\n",dist[E][1],degree[E][1]);
    }return 0;
}
