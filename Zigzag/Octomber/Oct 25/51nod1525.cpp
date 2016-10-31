#include <bits/stdc++.h>
using namespace std;
#define maxn 220000
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r

int f[maxn];
int col[maxn<<2], cov[maxn<<2];
int n,m,last;

int read() {
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}

int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}

void merge(int x, int y){
	int fx=find(x), fy=find(y);
	if (fx!=fy) f[fx]=fy;
}

void update(int x){
	if (col[x<<1]==col[x<<1|1]) col[x]=col[x<<1];
	else col[x]=0;
}

void color(int x, int z){
	col[x]=cov[x]=z;
}

void down(int x){
	if (!cov[x]) return ;
	color(x<<1, cov[x]);
	color(x<<1|1, cov[x]);
	cov[x]=0;
}

void query(int x, int l, int r, int ll, int rr, int z){
	if (l==r || ll<=l && r<=rr && col[x]){
		color(x, z); 
		merge(l, z);
		return ;
	}
	down(x);
	int mid=(l+r)>>1;
	if (ll<=mid) query(lson,ll,rr, z);
	if (rr> mid) query(rson,ll,rr, z);
	update(x);
}

int main()
{
	n=read(); m=read();
	for (int i=1;i<=n;i++) f[i]=i;
	int x, y, sign;
	for (int i=1;i<=m;i++){
		sign=read(); x=read(); y=read();
		if (sign==1){
			merge(x,y);
		}
		else if (sign==2){
			query(1,1,n,x,y,find(x));
		}
		else{
			int fx=find(x), fy=find(y);
			printf((fx==fy)?"YES\n":"NO\n");
		}
	}
	return 0;
}