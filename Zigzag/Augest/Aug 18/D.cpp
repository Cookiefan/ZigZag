#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long ll;
typedef ll LL;

const int maxn = 3000200;
int n, k, m;
int ans[maxn];
int del[maxn];
int delcnt;

int c[maxn*4];

inline void update(int x)
{
  c[x]=c[x<<1]+c[x<<1|1];
}

inline void change(int x, int l, int r, int p, int z)
{
  if (l==r)
  {
    c[x]+=z;
    return ;
  }
  int mid=(l+r)>>1;
  if (p<=mid) change(x<<1, l, mid, p, z);
  else change(x<<1|1, mid+1, r, p, z);
  update(x);
}

inline int query(int x, int l, int r, int k)
{
  if (l==r)
  {
    return l;
  }
  int mid=(l+r)>>1;
  if (k<=c[x<<1]) return query(x<<1, l, mid, k);
  else return query(x<<1|1, mid+1, r, k-c[x<<1]);
}

inline void solve()
{
  int tot = n;
  int now = 1; 
  delcnt = 0;
  memset(c,0,sizeof(c));
  for (int i=1;i<=n;i++) change(1,1,n,i,1);
  for (int i = 1; i <= n; i++)
  {
    int x=query(1,1,n,now);
    del[delcnt++] = x;
    now = now + k;
    ans[i] = x;
    if (now > tot)
    {
      tot -= delcnt;
      for (int i = 0; i < delcnt; i++)
      {
        change(1,1,n,del[i],-1);
      }
      now = 1;
      delcnt = 0;
    }
  }
}



int main()
{
  // #ifndef ONLINE_JUDGE
  // freopen("data.in", "r", stdin);
  // #endif
  int T;
  scanf("%d", &T);
  while(T--)
  {
    scanf("%d%d%d", &n, &k, &m);
    solve();
    int t;
    while(m--)
    {
      scanf("%d", &t);
      printf("%d\n", ans[t]);
    }
  }
  return 0;
}
