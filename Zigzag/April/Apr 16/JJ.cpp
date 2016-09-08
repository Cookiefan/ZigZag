#include <bits/stdc++.h>
using namespace std;
int n;
int a[1020];
int mark[1020];
char out[1020];
int main()
{
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
      a[i] = rand() % 2;
    int info;
    int pos = 0;
    int state = 0;
    while(true)
    {
      memset(out, 0, sizeof(out));
      for (int i = 0; i < n; i++)
        sprintf(out + i, "%d", a[i]);
      printf("%s\n", out);
      fflush(stdout);
      scanf("%d", &info);
      if(info == n) break;
      if(state == 0)
      {
        if(info == n/2)
        {
          state = 1;
          pos = 1;
          mark[0] = 0;
          a[0] ^= 1;
          a[1] ^= 1;
        }
        else
        {
          for (int i = pos + 1; i < n; i++)
            a[i] ^= 1;
          pos++;
        }
      }
      else if(state == 1)
      {
        if(info == 0)
        {
          mark[pos] = 0;
          a[0] ^= 1;
          a[pos] ^= 1;
        }
        else 
        {
          mark[pos] = 1;
          a[0] ^= 1;
          a[pos] ^= 1;
        }
        pos++;
        if(pos >= n)
        {
          state = 2;
          for (int i = 0; i < n; i++)
            a[i] ^= mark[i];
        }
        else
        {
          a[0] ^= 1;
          a[pos] ^= 1;
        }
      }
      else if(state == 2)
      {
        for (int i = 0; i < n; i++)
          a[i] ^= 1;
      }
    }
    return 0;
}
