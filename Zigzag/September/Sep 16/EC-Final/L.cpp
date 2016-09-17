#include <bits/stdc++.h>
#define maxn 2200
using namespace std;
int a[maxn][maxn];
typedef long long LL;
struct tii
{
	LL x, y, v;
};
vector<tii> q;
int n,m;
bool flag;

inline int read() {
    int x=0;char c=getchar();
    for(;!isdigit(c);c=getchar()) if (c=='?') return -1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x;
}

int judge(LL x, LL y)
{
	int ss=q.size();
	for (int i=0;i<ss;i++){
		LL xx=q[i].x-q[0].x+x, yy=q[i].y-q[0].y+y;
		if (xx*yy!=q[i].v) return 0;
	}
	return 1;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x; q.clear();
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				x=read();
				if (x>0) q.push_back((tii){i, j, x});
			}
		if (q.size()==0) flag=1;
		else{
			flag=0;
			for (int i=1;i*i<=q[0].v;i++)
				if (q[0].v%i==0){
					int j=q[0].v/i;
					if (i>=q[0].x && j>=q[0].y && judge(i, j)){
						flag=1;
						break;
					}
					if (j>=q[0].x && i>=q[0].y && judge(j, i)){
						flag=1;
						break;
					}
				}
		}
		printf(flag?"Case #%d: Yes\n":"Case #%d: No\n",o);
	}
	return 0;
}
// 2 2
// 998001 ?
// ? 1000000