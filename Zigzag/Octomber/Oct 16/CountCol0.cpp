#include <bits/stdc++.h>
#define maxn 200200
#define maxm 10000020
using namespace std;

int lc[maxm], rc[maxm], s[maxm];
int a[maxn], rot[maxn];
set<int> col[maxn];
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

void add(int p, int x, int z){
	for (int i=p;i<=n;i+=(i&-i)){
		rot[i]=change(rot[i], 0, n, x, z);
	}
}

int ask(int p, int x){
	int tmp=0;
	for (int i=p;i>=1;i-=(i&-i)){
		tmp+=query(rot[i], 0, n, x);
	}
	return tmp;
}

int main()
{
	freopen("CC.in","r",stdin);
	scanf("%d%d",&n,&m);
	int tot=0;
	for (int i=1;i<=10;i++) col[i].clear();
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		col[a[i]].insert(i);
		tot=max(a[i],tot);
	}
	for (int i=1;i<=tot;i++){
		col[i].insert(0);
		col[i].insert(n+1);
	}
	rot[0]=build(0,n);
	for (int i=1;i<=n;i++) rot[i]=rot[0];
	for (int i=1;i<=n;i++){
		int pre=*(--col[a[i]].lower_bound(i));
		add(i, pre, 1);
	}
	char sign;
	int x,y,pre,nxt;
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
			pre=*(--col[a[x]].lower_bound(x));
			nxt=*(++col[a[x]].lower_bound(x));
			//cout<<pre<<' '<<nxt<<endl;
			add(x, pre, -1);
			if (nxt!=n+1){
				add(nxt, x, -1);
				add(nxt, pre, 1);
			}

			col[a[x]].erase(x);
			a[x]=y;
			col[a[x]].insert(x);
			//for (auto t:col[a[x]]) cout<<t<<' '; cout<<endl;
			pre=*(--col[a[x]].lower_bound(x));
			nxt=*(++col[a[x]].lower_bound(x));
			//cout<<pre<<' '<<nxt<<endl;
			add(x, pre, 1);
			if (nxt!=n+1){
				add(nxt, pre, -1);
				add(nxt, x, 1);
			}
		}
	}
	return 0;
}