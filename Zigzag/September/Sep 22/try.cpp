#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#define mem(a , b) memset(a , b , sizeof(a))
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define lson step << 1
#define rson step << 1 | 1
using namespace std;
typedef long long LL;
const int N = 50005;  
//FFT copy from kuangbin  
const double pi = acos (-1.0);  
// Complex  z = a + b * i    
struct Complex {  
    double a, b;  
    Complex(double _a=0.0,double _b=0.0):a(_a),b(_b){}  
    Complex operator + (const Complex &c) const {  
        return Complex(a + c.a , b + c.b);  
    }  
    Complex operator - (const Complex &c) const {  
        return Complex(a - c.a , b - c.b);  
    }  
    Complex operator * (const Complex &c) const {  
        return Complex(a * c.a - b * c.b , a * c.b + b * c.a);  
    }  
};  
//len = 2 ^ k  
void change (Complex y[] , int len) {  
    for (int i = 1 , j = len / 2 ; i < len -1 ; i ++) {  
        if (i < j) swap(y[i] , y[j]);  
        int k = len / 2;  
        while (j >= k) {  
            j -= k;  
            k /= 2;  
        }  
        if(j < k) j += k;  
    }   
}  
// FFT   
// len = 2 ^ k  
// on = 1  DFT    on = -1 IDFT  
void FFT (Complex y[], int len , int on) {  
    change (y , len);  
    for (int h = 2 ; h <= len ; h <<= 1) {  
        Complex wn(cos (-on * 2 * pi / h), sin (-on * 2 * pi / h));  
        for (int j = 0 ; j < len ; j += h) {  
            Complex w(1 , 0);  
            for (int k = j ; k < j + h / 2 ; k ++) {  
                Complex u = y[k];  
                Complex t = w * y [k + h / 2];  
                y[k] = u + t;  
                y[k + h / 2] = u - t;  
                w = w * wn;  
            }  
        }  
    }  
    if (on == -1) {  
        for (int i = 0 ; i < len ; i ++) {  
            y[i].a /= len;  
        }  
    }  
}  
struct Edge {
    int v , next;
}e[N << 1];
int n , tot , start[N];
int prime[N] , flag[N] , primecnt;
int del[N] , size[N];
LL ans = 0;
void Init (int n) {
    mem (start , -1);
    tot = 0;
    primecnt = 0;
    for (int i = 2 ; i < n ; i ++) {
        if (flag[i]) continue;
        prime[primecnt ++] = i;
        for (int j = 2 ; j * i < n ; j ++) 
            flag[i * j] = 1;
    }
}
void _add (int u , int v) {
    e[tot].v = v; e[tot].next = start[u];
    start[u] = tot ++;
}
void add (int u , int v) {
    _add (u , v);
    _add (v , u);
}
void cal (int u , int pre) {
    size[u] = 1;
    for (int i = start[u] ; i != -1 ; i = e[i].next) {
        int v = e[i].v;
        if (v == pre || del[v]) continue;
        cal (v , u);
        size[u] += size[v];
    }
}
int newroot , maxsize , totalsize;
void dfs (int u , int pre) {
    int mx = 0 , sum = 1;
    for (int i = start[u] ; i != -1 ; i = e[i].next) {
        int v = e[i].v;
        if (v == pre || del[v]) continue;
        dfs (v , u);
        mx = max (mx , size[v]);
    }
    mx = max (mx , totalsize - size[u]);
    if (mx < maxsize) maxsize = mx , newroot = u;
}
int search (int r) {
    cal (r , -1);
    totalsize = size[r];
    maxsize = 1 << 30;newroot = -1;
    dfs (r , -1);
    return newroot;
}
int dist[N] , idx , cnt[N];
vector <int> sub[N] , all;
Complex x1[N << 2];
LL sum [N << 2];
LL fuck (vector<int> &v) {
    if (v.size() == 0) return 0;
    int len = v[v.size() - 1] + 1;
    for (int i = 0 ; i < len ; i ++) {
        cnt[i] = 0;
    }
    for (int i = 0 ; i < v.size() ; i ++) {
        cnt[v[i]] ++ ;
    }
    int l = 1;
    while (l < len * 2) l <<= 1;
    for (int i = 0 ; i < len ; i ++) {
        x1[i] = Complex (cnt[i] , 0);
    }
    for (int i = len ; i < l ; i ++) {
        x1[i] = Complex (0 , 0);
    }
    FFT (x1 , l , 1);
    for (int i = 0 ; i < l ; i ++) {
        x1[i] = x1[i] * x1[i];
    }
    FFT (x1 , l , -1);
    l = 2 * v[v.size() - 1];
    LL ans = 0LL;
    for (int i = 0 ; i <= l ; i ++) {
        sum[i] = (LL)(x1[i].a + 0.5);
    }
    for (int i = 0 ; i < v.size() ; i ++)
        sum[v[i] << 1] --;
    for (int i = 0 ; i <= l ; i ++) {
        sum[i] /= 2;
    }
    for (int i = 0 ; i < primecnt && prime[i] <= l ; i ++) {
        ans += sum[prime[i]];
    }
    return ans;
}
void gao (int u , int pre) {
    all.push_back (dist[u]);
    sub[idx].push_back (dist[u]);
    for (int i = start[u] ; i != -1 ; i = e[i].next) {
        int v = e[i].v;
        if (v == pre || del[v]) continue;
        dist[v] = dist[u] + 1;
        gao (v , u);
    }
}
void solve (int root) {
    root = search (root);
    del[root] = 1;
    if (totalsize == 1) return ;
    idx = 0 ; all.clear();
    for (int i = start[root] ; i != - 1 ; i = e[i].next) {
        int v = e[i].v;
        if (del[v]) continue;
        sub[idx].clear();
        dist[v] = 1;
        gao (v , -1);
        sort (sub[idx].begin() , sub[idx].end());
        idx ++;
    }
    all.push_back(0);
    sort (all.begin() , all.end());
    ans += fuck (all);
    for (int i = 0 ; i < idx ; i ++) {
        ans -= fuck (sub[i]);
    }
    for (int i = start[root] ; i != -1 ; i = e[i].next) {
        int v = e[i].v;
        if (del[v]) continue;
        solve (v);
    }
}
int main () {
    //freopen ("A.in" , "r" , stdin);
    scanf ("%d" , &n);
    Init(n);
    for (int i = 1 ; i < n ; i ++) {
        int u , v;
        scanf ("%d %d" , &u , &v);
        add (u , v);
    }
    solve (1);
    printf ("%.7f\n" , ans / (n * 0.5 * (n - 1)));
    return 0;
}