#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 62;

ll memo[N][N][N][N][2];
ll solve(int p1, int p2, int p3, int p4, bool ok) {
	if(p1 + p2 + p3 + p4 == 0) return ok;
	ll &r = memo[p1][p2][p3][p4][ok];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i < p1; i++)
		r += solve(i, p1 - 1 - i + p2, p3, p4, ok);
	for(int i = 0; i < p2; i++)
		r += solve(p1, i, p2 - 1 - i + p3, p4, ok);
	for(int i = 0; i < p3; i++)
		r += solve(p1, p2, i, p3 - 1 - i + p4, true);
	// so pode ser o ultimo ou teria LIS de tamanho >=5
	if(p4) r += solve(p1, p2, p3, p4 - 1, true);
	return r = mod(r);
}

int main() {
	ll fat = 1;
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) fat = mod(fat * ll(i));
	memset(memo, -1, sizeof memo);
	printf("%lld\n", mod(fat - solve(n, 0, 0, 0, 0) + modn));
}
