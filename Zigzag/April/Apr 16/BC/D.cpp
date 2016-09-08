#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

int aa[30], rr[30];
int tmp[30];
int tmp1[30];
int vis[30];
int n;

void EXT_GCD(LL a, LL b, LL &d, LL &x, LL &y)
{
  if(!b) {d = a, x = 1, y = 0;}
  else {EXT_GCD(b, a % b, d, y, x), y -= x * (a / b);}
}
LL mega_mod(int n)
{
  LL a1, a2, r1, r2, d, c, x, y, x0,s;
  bool flag = true;
  a1 = aa[1], r1 = rr[1];
  for(int i = 1; i < n; i++)
  {
    a2 = aa[i+1], r2 = rr[i+1];
    if(!flag) continue;
    c = r2 - r1;
    EXT_GCD(a1, a2, d, x, y);
    if(c%d!=0)
    {
      flag = false;
      continue;
    }
    x0 = x*c/d;
    s = a2/d;
    x0 = (x0%s+s)%s;
    r1=r1+x0*a1;
    a1=a1*a2/d;
  }
  if(flag) return r1;
  else return -1LL;
}

LL GCD(LL a, LL b)
//递归
{
  if(a < b) swap(a, b);
  LL r = a % b;
  if(r == 0) return b;
  return GCD(b, r);
}

LL LCM(LL a, LL b)
{
    return a * b / GCD(a, b);
}

LL calans()
{
    LL ret = aa[1];
    for (int i = 2; i <= n; i++)
      ret = LCM(ret, aa[i]);
    return ret;
}


int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
      scanf("%d", &n);
      memset(aa, 0, sizeof(aa));
      memset(rr, 0, sizeof(rr));
      memset(vis, 0, sizeof(vis));
      for (int i = n; i >= 1; i--)
      {
        scanf("%d", &tmp1[i]);
        tmp[tmp1[i]] = i;
      }

      int now = 1;
      for (int rest = n; rest >= 1; rest --)
      {
        aa[rest] = rest;
        rr[rest] = 1;
        while(now != tmp[rest])
        {
          if(vis[now] == 0)
            rr[rest]++;
          now ++;
          if(now > n) now = 1;
        }
        vis[now] = 1;
        rr[rest] %= rest;
      }

      // for (int i = 1; i <= n; i++)
      //   printf("%d %d\n", aa[i], rr[i]);

      LL ans = mega_mod(n);

      if(ans == -1) printf("Creation August is a SB!\n");
      else if(ans == 0) cout << calans() << endl;
      else cout << ans << endl;
    }
}

/*
1
7
7 6 5 4 3 2 1
*/
