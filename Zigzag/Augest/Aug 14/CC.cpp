#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
using namespace std;
typedef long long ll;

template <typename T> inline void R(T &x) {
    char ch = getchar(); x = 0;
    for (; ch<'0' || ch>'9'; ch = getchar());
    for (; ch<='9' && ch>='0'; ch=getchar()) x = x*10 + ch-'0';
}

const int N = 100005;
int n, ne, s[N], val[N], e[N * 2], h[N * 2], c[N * 2];
int f[N * 2][2], ans[N];
inline void NE(int x, int y, int z) {
    ++ne, e[ne] = y, h[ne] = s[x], c[ne] = z, s[x] = ne;
}
void dp1(int cw, int fa) {
    int x = e[cw], *cf = f[cw], mx = 0;
    cf[0] = val[x]; mx = 0;
    for (int w=s[x]; w; w=h[w]) if (e[w] != fa) {
        dp1(w, x);
        cf[0] += f[w][0];
        mx = max(mx, f[w][1] - f[w][0]);
    }
    cf[1] = cf[0] + mx;
    cf[0] = max(0, cf[0] - c[cw] * 2);
    cf[1] = max(0, cf[1] - c[cw]);
}
void dp2(int cw, int fa) {
    int x = e[cw], *cf, va;
    int mx1 = 0, mx2 = 0, mf = 0, sum = val[x];
    for (int w=s[x]; w; w=h[w]) {
        sum += f[w][0];
        va = f[w][1] - f[w][0];
        if (va > mx1)
            mx2 = mx1, mx1 = va, mf = w; else
        if (va > mx2)
            mx2 = va;
    }
    ans[x] = sum + mx1;
    for (int w=s[x]; w; w=h[w]) if (e[w] != fa) {
        cf = f[w ^ 1];
        cf[0] = sum - f[w][0];
        if (mf != w)
            cf[1] = mx1 + cf[0]; else
            cf[1] = mx2 + cf[0];
        cf[0] = max(0, cf[0] - c[w] * 2);
        cf[1] = max(0, cf[1] - c[w]);
    }
    for (int w=s[x]; w; w=h[w]) if (e[w] != fa)
        dp2(w, x);
}
void run() {
    R(n); ne = 1;
    for (int i=1; i<=n; ++i)
        R(val[i]), s[i] = 0;
    int x, y, z;
    for (int i=1; i<n; ++i) {
        R(x); R(y); R(z);
        NE(x, y, z);
        NE(y, x, z);
    }
    e[1] = 1;
    dp1(1, 0);
    dp2(1, 0);
    for (int i=1; i<=n; ++i)
        printf("%d\n", ans[i]);
}
int main() {
    int T;
    scanf("%d", &T);
    for (int i=1; i<=T; ++i) {
        printf("Case #%d:\n", i);
        run();
    }
    return 0;
}
