#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <string>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define X first
#define Y second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1000020;
int n;
int a[maxn];


int main()
{
  while(scanf("%d", &n) != EOF)
  {
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);

    int tmp = a[n];
    int ans = 0;  
    for (int i = n-1; i >= 1; i--)
    {
      if (tmp >= 0)
      {
        ans++;
        tmp = a[i];
      }
      else
      {
        tmp += a[i];
      }
    }
    printf("%d\n", ans + 1);
  }
  return 0;
}
