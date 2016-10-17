//对于每个数将它的pre插入到主席树中
//每次直接询问0..l-1中有多少次插入即可
#include <bits/stdc++.h>
#define maxn 20020
#define maxc 1000020
#define maxm 5000002
using namespace std;

int lc[maxm], rc[maxm], s[maxm];
int a[maxn], rot[maxn];
set<int> col[maxc];
typedef set<int>::iterator sit;
int num, n, m, ans, tot;

inline int build(int l, int r)
{
    int now=++num;
    if (l==r) return now;
    int mid=(l+r)>>1;
    lc[now]=build(l, mid);
    rc[now]=build(mid+1, r);
    return now;
}

inline int change(int x, int l, int r, int p, int z)
{
    int now=++num;
    lc[now]=lc[x];
    rc[now]=rc[x];
    s[now]=s[x]+z;
    if (l==r) return now;
    int mid=(l+r)>>1;
    if (p<=mid) lc[now]=change(lc[x], l, mid, p, z);
    else rc[now]=change(rc[x], mid+1, r, p, z);
    return now;
}

inline int query(int x, int l, int r, int p)
{
    if (l==r) return s[x];
    int mid=(l+r)>>1;
    if (p<=mid)
    	return query(lc[x], l, mid, p);
    else{
    	int cur=s[lc[x]];
    	return cur+query(rc[x], mid+1, r, p);
    }
}

inline void write(int x, int l, int r)
{
    if (l==r)
    {
        cout<<s[x]<<' ';
        return;
    }
    int mid=(l+r)>>1;
    write(lc[x], l, mid);
    write(rc[x], mid+1, r);
}

inline void add(int p, int x, int z){
	if (p==0) return ;
	for (int i=p;i<=n;i+=(i&-i)){
		rot[i]=change(rot[i], 0, n, x, z);
	}
}

inline int ask(int p, int x){
	int tmp=0;
	for (int i=p;i>=1;i-=(i&-i)){
		tmp+=query(rot[i], 0, n, x);
	}
	return tmp;
}

inline int prev(int c, int x){
	sit p=col[c].lower_bound(x);
	if (p!=col[c].begin()) return *(--p);
	else return 0;
}
inline int succ(int c, int x){
	sit p=col[c].upper_bound(x);
	if (p!=col[c].end()) return *p;
	else return 0;
}

int main()
{
	freopen("CC.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		col[a[i]].insert(i);
	}
	num=0;
	rot[0]=build(0,n);
	for (int i=1;i<=n;i++) rot[i]=rot[0];
	for (int i=1;i<=n;i++){
		int ll=prev(a[i],i);
		add(i, ll, 1);
	}
	char sign;
	int x,y,ll,rr;
	sit pre,nxt;
	for (int i=1;i<=m;i++){
		// for (int j=0;j<=n;j++){
		// 	cout<<j<<": ";
		// 	write(rot[j],0,n);
		// 	cout<<endl;
		// }
		// cout<<endl;
		scanf(" %c%d%d",&sign,&x,&y);
		if (sign=='Q'){
			//cout<<x-1<<' '<<y<<endl;
			printf("%d\n",ask(y, x-1)-ask(x-1, x-1));
		}
		else{
			ll=prev(a[x], x);
			rr=succ(a[x], x);
			add(x, ll, -1);
			if (rr){
				add(rr, x, -1);
				add(rr, ll, 1);
			}
			col[a[x]].erase(x);
			a[x]=y;
			col[a[x]].insert(x);
			ll=prev(a[x], x);
			rr=succ(a[x], x);
			add(x, ll, 1);
			if (rr){
				add(rr, x, 1);
				add(rr, ll, -1);
			}
		}
	}
	return 0;
}