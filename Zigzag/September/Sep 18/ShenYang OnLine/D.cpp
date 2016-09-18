/*
 *******************************
 * author :   poore            *
 * mail   :   py100c@gmail.com *
 * from   :   Chongqing, China *
 *******************************
 */

#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long ll;
typedef ll LL;
typedef pair<int,int> pii;
template <class T>
inline void RD(T &x) {
  char c=getchar(); 
  x=0;
  while(!isdigit(c))
    c=getchar();
  while(isdigit(c)){ 
    x=x*10+c-'0';
    c=getchar(); 
  }
}
const int SZ = 3;
ll oo = 1e9+7;

struct matrix {
  ll m[SZ][SZ];
  matrix() {
    memset(m, 0, sizeof(m));
  }
  matrix(int x) {
    memset(m, 0, sizeof(m));
    for (int i = 0; i < SZ; i++) m[i][i] = x;
  }
  void clear() {
    memset(m, 0, sizeof(m));
  }
  friend matrix operator *(matrix a, matrix b) {
    matrix c;
    for (int k = 0; k < SZ; k++)
      for (int i = 0; i < SZ; i++) if (a.m[i][k])
        for (int j = 0; j < SZ; j++)
          (c.m[i][j]+=a.m[i][k]*b.m[k][j]%oo)%=oo;
    return c;
  }
  friend matrix operator ^(matrix e, ll k) {
    matrix tmp = matrix(1);
    while(k) {
      if (k&1) tmp = tmp*e;
      k>>=1;
      e=e*e;
    }
    return tmp;
  }
  void show() {
    printf("============\n");
    for (int i = 0; i < SZ; i++)
      for (int j = 0; j < SZ; j++)
        printf("%I64d%c", m[i][j], j == SZ-1? '\n':' ');
    printf("============\n");
  }
};
matrix per, M;
LL pow_mod(LL a, LL b, LL p)
{
  LL ret = 1;  
  while(b) {  
    if(b & 1) ret = (ret*a)%p;  
    a = (a*a)%p;  
    b >>= 1;  
  }  
  return ret%p;  
}

//欧拉函数
long long phi(long long x)
{
	long long cnt=x;
	for (long long i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x>1) cnt=cnt/x*(x-1);
	return cnt;
}

ll solve(ll pp)
{
  per.clear();
  per.m[0][0] = 4;
  per.m[0][1] = 1;
  per.m[0][2] = 1;
  per.m[1][0] = 1;
  per.m[1][1] = 0;
  per.m[1][2] = 0;
  per.m[2][0] = 8;
  per.m[2][1] = 0;
  per.m[2][2] = 1;
  M.clear();
  M.m[0][0] = 1;
  //cout << pp << endl;
  per = per^(pp);
  M = M*per;
  //M.show();
  return M.m[0][2];
}

int main()
{
  //freopen("data.in", "r", stdin);
  int T;
  /*
  cout << solve(0) << endl;
  cout << solve(1) << endl;
  cout << solve(2) << endl;
  */
  scanf("%d", &T);
  ll n, x, y, s;
  while (T--)
  {
    scanf("%I64d%I64d%I64d%I64d", &n, &y, &x, &s);
    oo = phi(s+1);
    ll tmp = solve(n*y);
    //printf("tmp = %I64d\n", tmp);
    //x %= oo;
    tmp = pow_mod(x, tmp, s+1);
    printf("%I64d\n", tmp);
  }
  return 0;
}

