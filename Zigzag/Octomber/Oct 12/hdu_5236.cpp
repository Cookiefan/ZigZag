#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+20;
const double inf = 1e20;

double e[maxn], ans[maxn];
double pn[maxn];
double p;
int n, x;

const double eps = 1e-8;

int dcmp(double x) {
  if (fabs(x)<eps) return 0;
  return x<0? -1:1;
}


void pre() {
  pn[0] = 1.0;
  for (int i = 1; i <= n; i++) {
    pn[i] = pn[i-1]*p;
  }

  /*
  cout << "pn" << endl;
  for (int i = 0; i <= n; i++) {
    printf("%.4f ", pn[i]);
  }
  cout << endl;
  */

  for (int i = 0; i <= n; i++) {
    e[i] = (1.0/pn[i]-1.0)/(1.0-p);
  }
}

double cal(int mid, int k) {
  return ans[mid] + e[k-mid] + x*1.0;
}

void solve() {
  ans[0] = 0.0;
  int low, high, mid1, mid2;
  double ans1, ans2;
  for (int i = 1; i <= n; i++) {
    low = 0, high = i;
    while(low + 2000 <= high) {
      mid1 = low+(high-low)/3;
      mid2 = high-(high-low)/3;
      ans1 = cal(mid1, i);
      ans2 = cal(mid2, i);
      if (dcmp(ans1-ans2) < 0) 
        high = mid2;
      else
        low = mid1;
    }
    ans[i] = inf;
    //cout << low << "----" << high << endl;
    //cout << x << endl;
    for (int j = low; j <= high; j++) {
      //printf("cal %d,%d = %.4f\n",j,i, cal(j,i));
      ans[i] = min(ans[i], cal(j, i));
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int ka=1; ka <= T; ka++) {
    scanf("%d%lf%d", &n,&p,&x);
    p = 1.0-p;
    pre();
    //cout << "e[]  ===========" << endl;
    /*
    for (int i = 0; i <= n; i++)
      printf("%.4f ", e[i]);
    printf("\n");
    */
    solve();
    /*
    for (int i = 0; i <= n; i++)
      printf("%.4f ", ans[i]);
    printf("\n");
    */
    printf("Case #%d: %.7f\n", ka, ans[n]);
  }
  return 0;
}
