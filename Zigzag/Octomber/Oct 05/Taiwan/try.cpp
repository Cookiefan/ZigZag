#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <bitset>
#include <queue>
#include <set>
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;

#define LL long long 
#define ULL unsigned long long
#define eps 1e-9
#define N (200000 + 10)
#define pii pair<int,int>
#define MP make_pair
#define PB push_back
#define inf 0x3f3f3f3f
#define md (ll+rr>>1)
#define lson ll, md, ls
#define rson md + 1, rr, rs
#define ls i<<1
#define rs i<<1|1
#define mod 1000003
#define MOD 1000003  
#define K 3  
  
const int m[K] = {1004535809, 998244353, 104857601};  
#define G 3  
  
  
int qpow(int x, int k, int P) {  
    int ret = 1;  
    while(k) {  
        if(k & 1) ret = 1LL * ret * x % P;  
        k >>= 1;  
        x = 1LL * x * x % P;  
    }  
    return ret;  
}  
  
struct _NTT {  
    int wn[25], P;  
  
    void init(int _P) {  
        P = _P;  
        for(int i = 1; i <= 21; ++i) {        
            int t = 1 << i;        
            wn[i] = qpow(G, (P - 1) / t, P);        
        }  
    }  
    void change(int *y, int len) {  
        for(int i = 1, j = len / 2; i < len - 1; ++i) {        
            if(i < j) swap(y[i], y[j]);        
            int k = len / 2;        
            while(j >= k) {        
                j -= k;        
                k /= 2;        
            }        
            j += k;        
        }   
    }  
    void NTT(int *y, int len, int on) {  
        change(y, len);        
        int id = 0;        
        
        for(int h = 2; h <= len; h <<= 1) {        
            ++id;        
            for(int j = 0; j < len; j += h) {        
                int w = 1;        
                for(int k = j; k < j + h / 2; ++k) {        
                    int u = y[k];        
                    int t = 1LL * y[k+h/2] * w % P;       
                    y[k] = u + t;        
                    if(y[k] >= P) y[k] -= P;        
                    y[k+h/2] = u - t + P;        
                    if(y[k+h/2] >= P) y[k+h/2] -= P;    
                    w = 1LL * w * wn[id] % P;  
                }        
            }        
        }        
        if(on == -1) {        
            for(int i = 1; i < len / 2; ++i) swap(y[i], y[len-i]);        
            int inv = qpow(len, P - 2, P);        
            for(int i = 0; i < len; ++i)     
                y[i] = 1LL * y[i] * inv % P;  
        }        
    }  
    void mul(int A[], int B[], int len) {  
        NTT(A, len, 1);  
        NTT(B, len, 1);  
        for(int i = 0; i < len; ++i) A[i] = 1LL * A[i] * B[i] % P;  
        NTT(A, len, -1);  
    }  
}ntt[K];  
  
int tmp[N][K], t1[N], t2[N];  
int r[K][K];  
  
int CRT(int a[]) {  
    int x[K];  
    for(int i = 0; i < K; ++i) {  
        x[i] = a[i];  
        for(int j = 0; j < i; ++j) {  
            int t = (x[i] - x[j]) % m[i];  
            if(t < 0) t += m[i];  
            x[i] = 1LL * t * r[j][i] % m[i];  
        }  
    }  
    int mul = 1, ret = x[0] % MOD;  
    for(int i = 1; i < K; ++i) {  
        mul = 1LL * mul * m[i-1] % MOD;  
        ret += 1LL * x[i] * mul % MOD;  
        if(ret >= MOD) ret -= MOD;  
    }  
    return ret;  
}  
  
void mul(int A[], int B[], int len) {  
    for(int id = 0; id < K; ++id) {  
  
        for(int i = 0; i < len; ++i) {  
            t1[i] = A[i];  
            t2[i] = B[i];  
        }  
        ntt[id].mul(t1, t2, len);  
        for(int i = 0; i < len; ++i)   
            tmp[i][id] = t1[i];  
    }  
    for(int i = 0; i < len; ++i) {  
        A[i] = CRT(tmp[i]);  
  
    }  
}  
  
void init() {  
    for(int i = 0; i < K; ++i) {  
        for(int j = 0; j < i; ++j) {  
            r[j][i] = qpow(m[j], m[i] - 2, m[i]);  
        }  
    }  
    for(int i = 0; i < K; ++i) {  
        ntt[i].init(m[i]);  
    }  
}  


int n, M, p;
int a[N], b[N];
int x1[N], x2[N];


void mymul(int *a, int *b, int cur) {
	int len = 1;
	while(len < 2 * M) len <<= 1;
	for(int i = 0; i < len; ++i) x1[i] = x2[i] = 0;
	for(int i = 0; i < M; ++i)  {
		x1[i] = a[i];
		x2[i*cur % M] += b[i];
	}

	mul(x1, x2, len);
	for(int i = 0; i < M; ++i) a[i] = 0;
	for(int i = 0; i < len; ++i) a[i%M] = (a[i%M] + x1[i] % mod) % mod;
}

void calc(int n, int &cur){ 
	if(n == 1) {
		cur = p;
		for(int i = 0; i < M; ++i) a[i] = 0;
		for(int i = 'A'; i <= 'Z'; ++i)
			++a[i%M];
		return ;
	}
	calc(n>>1, cur);
	mymul(a, a, cur);
	cur = cur * cur % M;
	if(n & 1) {
		for(int i = 0; i < M; ++i) b[i] = 0;
		for(int i = 'A'; i <= 'Z'; ++i) {
			for(int j = 0; j < M; ++j) {
				b[(i+j*p)%M] = (b[(i+j*p)%M] + a[j]) % mod;
			}
		}
		for(int i = 0; i < M; ++i) a[i] = b[i];
		cur = cur * p % M;
	}
}

int main() {
	init();
	scanf("%d%d%d", &n, &M, &p);
	int cur;
	calc(n, cur);
	int inv = qpow(2, mod-2, mod);
	int ans = 0;
	for(int i = 0; i <M; ++i) {
		ans = (ans + (LL) a[i] * (a[i] - 1 + mod) % mod * inv % mod) %mod;
	}
	printf("%d\n", ans);
}