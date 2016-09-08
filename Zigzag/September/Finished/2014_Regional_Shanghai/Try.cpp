#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MOD = 1e9 + 7;

int inv[MAXN], fact[MAXN];

int _inv(int x) {
    if(x == 1) return 1;
    return LL(MOD - MOD / x) * _inv(MOD % x) % MOD;
}

void init(int n = 100000) {
    fact[0] = 1;
    for(int i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * LL(i) % MOD;
    for(int i = 0; i <= n; ++i)
        inv[i] = _inv(fact[i]);
}

LL comb(int a, int b) {
    if(a < b) return 0;
    return LL(fact[a]) * inv[b] % MOD * LL(inv[a - b]) % MOD;
}

int dp[13][111];
int c[13];
int T, n, m, k;

int mulmul(LL a, LL b, LL c, LL d) {
    return a * b % MOD * c % MOD * d % MOD;
}

void update_add(int &a, int b) {
    a += b;
    if(a >= MOD) a -= MOD;
}

int solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][k] = 1;
    for(int i = 0, sum = n; i < m; ++i) {
        for(int r = 0; r <= k; ++r) if(dp[i][r]) {
            if(sum < 2 * r) break;
            for(int a = 0; a <= r; ++a) {
                for(int b = 0; b + a <= r; ++b) {
                    if(c[i + 1] - a - 2 * b < 0) break;
                    int t = mulmul(dp[i][r], comb(r, a), comb(r - a, b), comb(sum - 2 * r, c[i + 1] - a - 2 * b));
                    update_add(dp[i + 1][r - a - b], t);
                }
                if(i == m - 1) break; /// if i = m - 1 then a must be zero
            }
        }
        sum -= c[i + 1];
    }
    return dp[m][0];
}

int main() {
    init();
    //printf("%d\n", comb(10, 1));
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 1; i <= m; ++i) scanf("%d", &c[i]);
        printf("Case #%d: %d\n", t, solve());
    }
}