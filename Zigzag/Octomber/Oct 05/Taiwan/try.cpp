#include <cstdio>
#include <vector>
#define mul(x, y, z) (1ll * (x) * (y) % (z));

using namespace std;

const int mod = 1000003;
const int inv2 = 500002;
const int MOD[] = {998244353, 995622913};
const int ROOT[] = {3, 5};

int n, m, p, _x, _y ,P;
int a[30005], b[30005];
int A[1 << 16], B[1 << 16], C[1 << 16], AA[2][1<<16], BB[2][1 << 16],CC[2][1 << 16];
int Remain[2];

int qmod(int x, int n, int mod){
	int res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = mul(res, x, mod);
		x = mul(x, x, mod);
	}
	return res;
}

void ex_gcd(int a, int b, int &x, int &y) {
	if (!a) {
		x = 0, y = 1;
		return;
	}
	ex_gcd(b % a, a, x, y);
	int t = y;
	y = x;
	x = t - (b / a) * y;
}

long long china(const int m[], int b[]) {
	long long x, y, i, result, a1, m1, a2, m2;
	m1 = m[0], a1 = b[0];
	m2 = m[1]; a2 = b[1];
	x = _x, y = _y;
	result = (x * (a2 - a1) % m2 + m2) % m2;
	a1 = a1 + m1 * result;
	m1 = m1 * m2;
	a1 = (a1 % m1 + m1) % m1;
	return a1;
}	

namespace NTT {
	int n, p, mod, n_rev;
	vector<int> rb;
	int r[20];
	int ir[20];
	void work(int a[], int *roots);
	void init(int n, int mod, int root);
	void forward(int a[]) {
		work(a, r);
	}
	void reverse(int a[]) {
		work(a, ir);
		for (int i = 0; i < n; ++i) a[i] = mul(a[i], n_rev, mod);
	}
};

void NTT::init(int _n, int _mod, int root){
	n = _n, mod = _mod, rb.resize(n), p = 0;
	n_rev = qmod(n, mod - 2, mod);
	while ((1 << p) < n) ++p;
	for (int i = 0; i < n; ++i) {
		int x = i, y = 0;
		for (int j = 0; j < p; ++j) {
			y = (y << 1) | (x & 1);
			x >>= 1;
		}
		rb[i] = y;
	}
	int inv = qmod(root, mod - 2, mod);
	r[p - 1] = qmod(root, (mod - 1) / (1 << p), mod);
	ir[p - 1] = qmod(inv, (mod - 1) / (1 << p), mod);
	for (int i = p - 2; i >= 0; --i) {
		r[i] = mul(r[i + 1], r[i + 1], mod);
		ir[i] = mul(ir[i + 1], ir[i + 1], mod);
	}
}

void NTT::work(int a[], int *r) {
	for (int i = 0; i < n; ++i)
		if (rb[i] > i)
			swap(a[i], a[rb[i]]);
	for (int len = 2; len <= n; len <<= 1) {
		int root = *r++;
		for (int i = 0; i < n; i += len) {
			int w = 1;
			for (int j = 0; j < len / 2; ++j) {
				int u = a[i + j];
				int v = mul(a[i + j + len / 2], w, mod);
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
				w = mul(w, root, mod);
			}
		}
	}
}

void MUL(int A[], int B[], int C[], int n) {	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < n; ++j) AA[i][j] = A[j], BB[i][j] = B[j];
		NTT::init(n, MOD[i], ROOT[i]);
		NTT::forward(AA[i]);
		NTT::forward(BB[i]);
		for (int j = 0; j < n; ++j) CC[i][j] = mul(AA[i][j], BB[i][j], MOD[i]);
		NTT::reverse(CC[i]);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 2; ++j) Remain[j] = CC[j][i];
		C[i] = china(MOD, Remain) % mod;
	}
}

void calc(int a[], int b[], int c[], int p, int m) {
	int len = 1;
	while (len < m) len <<= 1;
	len <<= 1;
	for (int i = 0; i < len; ++i) A[i] = B[i] = 0;
	for (int i = 0; i < m; ++i) A[i * p % m] += a[i];
	for (int i = 0; i < m; ++i) B[i] += b[i];
	MUL(A, B, C, len);
	for (int i = 0; i < m; ++i) c[i] = 0;
	for (int i = 0; i < len; ++i) c[i % m] += C[i]; 
}

void Calc(int n, int &P) {
	if (n == 1) {
		P = p;
		for (int i = 0; i < m; ++i) a[i] = 0;
		for (int i = 'A'; i <= 'Z'; ++i) ++a[i % m];
		return;
	}
	Calc(n >> 1, P);
	calc(a, a, a, P, m);
	P = P * P % m;
	if (n & 1) {
		for (int i = 0; i < m; ++i) b[i] = 0;
		for (int i = 'A'; i <= 'Z'; ++i)
			for (int j = 0; j < m; ++j)
				b[(i + j * p) % m] = (b[(i + j * p) % m] + a[j]) % mod;
		for (int i = 0; i < m; ++i) a[i] = b[i];
		P = P * p % m;
	}
}

int main() {
	ex_gcd(MOD[0], MOD[1], _x, _y);
	scanf("%d%d%d", &n, &m, &p);
	Calc(n, P);
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		ans = (ans + 1ll * a[i] * (a[i] + mod - 1) % mod * inv2) % mod;
	}
	printf("%d\n", ans);
	return 0;
}