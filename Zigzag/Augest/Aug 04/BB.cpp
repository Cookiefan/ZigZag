#include <bits/stdc++.h>
#define maxn 1200
#define X first
#define Y second
using namespace std;
typedef long long LL;
typedef pair<LL,LL>pll;

LL frac[220000];
const LL oo=110119;

LL exp(LL a, LL b, LL p)
{
  a%=p;
  LL tmp=1;
  while (b)
  {
    if (b&1) tmp=(tmp*a)%p;
    a=a*a%p;
    b=b/2;
  }
  return tmp;
}

LL com(LL n,LL m,LL p)
{
  if (m>n) return 0;
  LL ans=frac[n]*exp(frac[m], p-2, p)%p*exp(frac[n-m], p-2, p)%p;
  return ans;
}

LL lucas(LL n,LL m,LL p)
{
  if (m==0) return 1;
  return com(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}

LL get_ans(LL dx, LL dy)
{
  if (!(dx>=0 && dy>=0 && dx*2>=dy && (dx*2-dy)%3==0 && (dy*2>=dx && (dy*2-dx)%3==0)))
    return 0;
  LL x=(dx*2-dy)/3;
  LL y=(dy*2-dx)/3;
  return lucas(x+y, y, oo);
}

LL ta[maxn];
int p;
LL n,m,ans;
vector<pll> pot;

int main()
{
  //freopen("data.in", "r", stdin);
  int o=0;
  frac[0]=1;
  for (int i=1;i<=oo;i++) frac[i]=frac[i-1]*i%oo;
  while (scanf("%I64d%I64d%d",&n,&m,&p)!=EOF)
  {
    LL tx, ty;
    ans = 0;
    pot.clear();
    for (int i=1;i<=p;i++)
    {
      scanf("%I64d%I64d",&tx,&ty);
      pot.push_back(pll(tx, ty));
    }
    sort(pot.begin(), pot.end());
    for (int i = 0; i < p; i++)
    {
      ta[i] = get_ans(pot[i].X-1, pot[i].Y-1);
      for (int j = 0; j < p; j++)
      {
        if (pot[j].X <= pot[i].X && pot[j].Y <= pot[i].Y)
          ta[i] = (ta[i] - ta[j]*get_ans(pot[i].X - pot[j].X, pot[i].Y - pot[j].Y)%oo+ oo) % oo;
      }
      //printf("tmp = %I64d\n", tmp);
      ans = (ans + ta[i] * get_ans(n-pot[i].X, m - pot[i].Y)%oo ) % oo;
    }

    ans = (get_ans(n-1, m-1) - ans + oo)%oo;

    printf("Case #%d: %I64d\n",++o,ans);
  }
  return 0;
}
