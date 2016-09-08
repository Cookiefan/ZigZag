#include <bits/stdc++.h>
#define maxn 5200
#define maxm 2000200
using namespace std;

struct edge
{
	int s, t, val, next;
}e[maxm];
int tot;
int fir[maxn];
void add_edge(int x, int y, int z)
{
	e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].val=z; e[tot].next=fir[y]; fir[y]=tot;
}

int main()
{
	return 0;
}