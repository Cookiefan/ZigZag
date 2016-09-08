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

const int maxn = 100020;
const int oo = 1e9+7;

int A[maxn], B[maxn], AB[maxn];
int fa, fb, fc, ba, bb, bc, n;
int arr[maxn];
int inqu[maxn];

void popA()
{
  // printf("A %d %d\n", fa, ba);
  while(inqu[A[ba]] == 0) ba--;
  printf("%d\n", arr[A[ba]]);
  inqu[A[ba--]] = 0;
}
void popB()
{
  // printf("B %d %d\n", fb, bb);
  while(inqu[B[bb]] == 0) bb--;
  printf("%d\n", arr[B[bb]]);
  inqu[B[bb--]] = 0;
}
void popAB()
{
  // printf("AB %d %d\n", fc, bc);
  while(inqu[AB[bc]] == 0) bc--;
  printf("%d\n", arr[AB[bc]]);
  inqu[AB[bc--]] = 0;
}


int main()
{
  #ifndef ONLINE_JUDGE
    //freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
  #endif
  int ka = 0;
  while(scanf("%d", &n))
  {
    if (n == 0) break;
    fa = fb = fc = 0;
    ba = bb = bc = 0;
    memset(arr, 0, sizeof(arr));
    memset(inqu, 0, sizeof(inqu));
    printf("Case #%d:\n", ++ka);
    char cmd[20];
    for (int i = 1; i <= n; i++)
    {
      scanf("%s", cmd);
      // printf("[%s]\n", cmd);
      if (cmd[1] == 'u')
      {
        scanf("%s%d", cmd, &arr[i]);
        inqu[i] = 1;
        char ch = cmd[0];
        if (ch == 'A')
        {
          A[++ba] = i;
        }
        else
        {
          B[++bb] = i;
        }
        AB[++bc] = i;
      }
      else if (cmd[1] == 'o')
      {
        scanf("%s", cmd);
        char ch = cmd[0];
        if (ch == 'A')
        {
          if (fa == ba) popAB();
          else popA();
        }
        else
        {
          if (fb == bb) popAB();
          else popB();
        }
      }
      else
      {
        char t1[10], t2[10];
        scanf("%s%s", t1, t2);
        fb = bb = 0;
        fa = ba = 0;
      }
    }
  }
  return 0;
}