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

inline int query(int x, int y, int l, int r, int p)
{
    if (l==r) return s[y]-s[x];
    int mid=(l+r)>>1;
    if (p<=mid)
    	return query(lc[x], lc[y], l, mid, p);
    else{
    	int cur=s[lc[y]]-s[lc[x]];
    	return cur+query(rc[x], rc[y], mid+1, r, p);
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
	for (int i=1;i<=tot;i++) col[i].insert(0);
	rot[0]=build(0,n);
	for (int i=1;i<=n;i++){
		int pre=*(--col[a[i]].lower_bound(i));
		rot[i]=change(rot[i-1],0,n,pre,1);
	}
	for (int i=0;i<=n;i++){
		cout<<i<<": ";
		write(rot[i],0,n);
		cout<<endl;
	}
	char sign;
	int x,y;
	for (int i=1;i<=m;i++){
		scanf(" %c%d%d",&sign,&x,&y);
		if (sign=='Q'){
			//cout<<x-1<<' '<<y<<endl;
			printf("%d\n",query(rot[x-1],rot[y],0,n,x-1));
		}
		else{

		}
	}
	return 0;
}