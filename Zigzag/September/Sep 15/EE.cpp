#include<stdio.h>
#include<algorithm>
#include<vector>
#define SZ 1024
using namespace std;
int n, A[1010], B[1010], L[1010];
vector<int>E[1010];
int cnt;
struct point{
    int a,b;
    bool operator <(const point &p)const{
        return a<p.a;
    }
}w[1010];
int IT[SZ+SZ+2];
void Ins(int a, int b){
    a+=SZ;
    IT[a]=b;
    while(a!=1){
        a>>=1;
        IT[a]=max(IT[a*2],IT[a*2+1]);
    }
}
int Get(int b, int e){
    b+=SZ,e+=SZ;
    int r = -1, t;
    while(b<=e){
        if(r<IT[b])r=IT[b],t=b;
        if(r<IT[e])r=IT[e],t=e;
        b=(b+1)>>1,e=(e-1)>>1;
    }
    if(r==-1)return -1;
    while(t<SZ){
        t*=2;
        if(IT[t]!=r)t++;
    }
    return t-SZ;
}
int Pos(int g){
    int i;
    for(i=0;i<cnt;i++){
        Ins(i, w[i].b);
    }
    for(int TT=0;TT<cnt;TT++){
        int b = 0, e = cnt - 1, r = -1, mid;
        while(b<=e){
            mid = (b+e)>>1;
            if(w[mid].a <= g){
                r = mid;
                b = mid + 1;
            }
            else e = mid - 1;
        }
        if(r==-1)return -1;
        int t = Get(0,r);
        if(t==-1)return -1;
        g += w[t].b-w[t].a;
        Ins(t,-1);
    }
    return g;
}
void DFS(int a){
    if(E[a].empty())return;
    int i;
    for(i=0;i<E[a].size();i++){
        DFS(E[a][i]);
    }
    cnt = 0;
    for(i=0;i<E[a].size();i++){
        int x = E[a][i], t;
        w[cnt].a = A[x] + L[x]*2, w[cnt].b = B[x];
        t = min(L[x], B[x]);
        w[cnt].a-=t, w[cnt].b-=t;
        cnt++;
    }
    sort(w,w+cnt);
    int bb = 0, ee = 1e9, mid, res, r2;
    while(bb<=ee){
        mid = (bb+ee)>>1;
        int t = Pos(mid);
        if(t==-1) bb = mid + 1;
        else{
            res = mid, r2 = t;
            ee = mid - 1;
        }
    }
    A[a] = res, B[a] = r2;
}
int main(){
    int i, c, a;
    scanf("%d",&n);
    n++;
    E[1].push_back(2);
    for(i=2;i<=n;i++){
        scanf("%d%d", &L[i],&c);
        if(!c){
            scanf("%d",&a);
            B[i] = a;
        }
        else{
            while(c--){
                scanf("%d",&a);
                a++;
                E[i].push_back(a);
            }
        }
    }
    DFS(1);
    printf("%d\n",A[1]);
}
