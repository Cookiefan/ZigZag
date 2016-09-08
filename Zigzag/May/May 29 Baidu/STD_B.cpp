#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
#define rep(i,n) for(int i = 0 ; i<(int)n;i++)
#define rep1(i,x,y) for(int i=(int)x;i<=(int)y;i++)
#define lowbit(x) (x&-x)

const int mod = 1000000009;
const int N = 14;
int d[1<<N][N];
int ma[N][N];
int n,m,K,cnt[1<<N];
int wei(int x){
     int ans = 0;
     while(x > 0){
         x>>=1;
         ans++;
     }
     return ans - 1;
}
int mi[N * N + N];
int f[1<<N],g[1<<N];
int main()
{
   mi[0] = 1;
   rep1(i , 1 , N*N) mi[i] = mi[i - 1] * 2 % mod;
   int T;
   int kase = 1;
   scanf("%d",&T);
   while(T--){
      scanf("%d %d %d",&n,&m,&K);
      memset(ma , 0, sizeof(ma));
      rep(i , m){
          int x , y;
          scanf("%d %d",&x,&y);
          --x; --y;
          ma[x][y] = ma[y][x] = 1;
      }
      cnt[0] = 0;
      for(int i =1; i < (1<<n); i++){
          cnt[i] = cnt[i-lowbit(i)];
          int k = wei(lowbit(i));
          rep(j , n){
              if((i>>j)&1)
                  cnt[i] += ma[j][k];
          }
      }

      f[0] = 0; g[0] = 1;
      for(int s = 1; s < (1<<n) ; s++){
            g[s] = 0;
            for(int j =(s - 1) & s ; j != 0 ; j = (j - 1)& s) if(j&(lowbit(s))){
                  g[s] = (g[s] + (ll)g[s - j] * f[j] % mod) % mod;
            }
            f[s] = (mi[cnt[s]] - g[s] + mod) % mod;
            g[s] = (g[s] + f[s]) % mod;
      }

      d[0][0] = 1;
      for(int s = 1; s<(1<<n) ; s++){
          for(int k = 0; k<=K;k++){
                d[s][k] = 0;
                if(k == 0)  continue;
                for(int j = s ; j ; j=(j-1)&s)if(j&(lowbit(s))){
                     d[s][k] = (d[s][k] + (ll)d[s - j][k - 1] * f[j] % mod) % mod;
                }
          }
      }
      printf("Case #%d:\n",kase++);
      printf("%d\n",(d[(1<<n)-1][K] + mod) %mod);
   }
    return 0;
}
