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
const int oo = 1e9+7;

char str[10][10];
int a[10][10], cnt;
int dx[4] = {0,0,1,1};
int dy[4] = {0,1,0,1};

vector<pii> pos;
bool found;



bool check1(int x, int y)
{
  int vis[5] = {0};
  for (int i = 0; i < 4; i++)
  {
    int tx = x + dx[i];
    int ty = y + dy[i];
    vis[a[tx][ty]]++;
    if (vis[a[tx][ty]] > 1 && a[tx][ty] != 0) return false;
  }
  return true;
}

bool check()
{
  
  for (int i = 0; i < 4; i++)
  {
    int vis[5] = {0};
    for (int j = 0; j < 4; j++)
    {
      vis[a[i][j]]++;
      if (vis[a[i][j]] > 1 && a[i][j] != 0) return false;
    }
  }
  for (int i = 0; i < 4; i++)
  {
    int vis[5] = {0};
    for (int j = 0; j < 4; j++)
    {
      vis[a[j][i]]++;
      if (vis[a[j][i]] > 1 && a[j][i] != 0) return false;
    }
  }
  return check1(0,0) && check1(0,2) && check1(2,0) && check1(2,2);
}

void dfs(int t)
{
  if (t >= cnt)
  {
    found = true;
    return;
  }
  for (int i = 1; i <= 4 && (!found); i++)
  {
    a[pos[t].X][pos[t].Y] = i;
    if (check())
      dfs(t+1);
  }
}


int main()
{
//   #ifndef ONLINE_JUDGE
//     freopen("data.in", "r", stdin);
// //    freopen("data.out", "w", stdout);
//   #endif
  int T;
  scanf("%d", &T);
  for (int ka = 1; ka <= T; ka++)
  {
    for (int i = 0; i < 4; i++)
      scanf("%s", str[i]);
    memset(a, 0, sizeof(a));
    pos.clear();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
      {
        if (str[i][j] == '*')
          pos.push_back(pii(i, j));
        else
          a[i][j] = str[i][j] - '0';
      }
    found = false;
    cnt = pos.size();
    dfs(0);
    printf("Case #%d:\n", ka);
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
        printf("%d", a[i][j]);
      printf("\n");
    }
  }
}
