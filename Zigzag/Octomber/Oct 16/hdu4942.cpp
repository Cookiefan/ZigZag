#include <bits/stdc++.h>
using namespace std;
#define maxn 100020
#define oo 1000000007
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
typedef long long LL;
int q[maxn], id[maxn], ll[maxn], rr[maxn], lc[maxn], rc[maxn], fa[maxn];
LL key[maxn], sum[maxn], mul[maxn<<2];
int n,m,rot,num;

void dfs(int x){
	if (lc[x]) dfs(lc[x]);
	q[++num]=x; id[x]=num;
	if (rc[x]) dfs(rc[x]);

	if (lc[x]) ll[x]=ll[lc[x]]; else ll[x]=id[x];
	if (rc[x]) rr[x]=rr[rc[x]]; else rr[x]=id[x];
	sum[x]=(sum[lc[x]]+sum[rc[x]]+key[x])%oo;
}

void update(int x){
	mul[x]=mul[x<<1]*mul[x<<1|1]%oo;
}

void build(int x, int l, int r){
	if (l==r){
		mul[x]=sum[q[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
	update(x);
}

void modify(int x, int l, int r, int p, LL z){
	if (l==r){
		mul[x]=z;
		return ;
	}
	int mid=(l+r)>>1;
	if (p<=mid) modify(lson,p,z);
	else modify(rson,p,z);
	update(x);
}

LL query(int x, int l, int r, int ll, int rr){
	if (ll<=l && r<=rr)
		return mul[x];
	int mid=(l+r)>>1;
	LL tmp=1;
	if (ll<=mid) (tmp*=query(lson,ll,rr))%=oo;
	if (rr>mid) (tmp*=query(rson,ll,rr))%=oo;
	return tmp;
}

int main()
{
	//freopen("splay.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++){
		scanf("%d%d",&n,&m);
		memset(key,0,sizeof(key));
		memset(sum,0,sizeof(sum));
		memset(ll,0,sizeof(ll));
		memset(rr,0,sizeof(rr));
		memset(fa,0,sizeof(fa));
		for (int i=1;i<=n;i++){
			scanf("%d%d%d",&key[i],&lc[i],&rc[i]);
			if (lc[i]) fa[lc[i]]=i;
			if (rc[i]) fa[rc[i]]=i;
		}
		num=0;
		dfs(1);
		// for (int i=1;i<=n;i++)
		// 	cout<<q[i]<<' ';
		// cout<<endl;
		build(1,1,n);
		int sign,x,y,z;
		printf("Case #%d:\n",o);
		for (int i=1;i<=m;i++){
			scanf("%d%d",&sign,&x);
			if (sign==0){
				y=lc[x];
				if (!y) continue;
				z=fa[x];
				if (z){
					if (x==lc[z]) lc[z]=y;
					else rc[z]=y;
				}
				lc[x]=rc[y];
				rc[y]=x;
				fa[x]=y; fa[y]=z;
				if (lc[x]) fa[lc[x]]=x;
				if (lc[x]) ll[x]=ll[lc[x]];
				else ll[x]=id[x];
				rr[y]=rr[x];
				sum[x]=(sum[lc[x]]+sum[rc[x]]+key[x])%oo;
				sum[y]=(sum[lc[y]]+sum[rc[y]]+key[y])%oo;
				modify(1,1,n,id[x],sum[x]);
				modify(1,1,n,id[y],sum[y]);
			}
			else if (sign==1){
				y=rc[x];
				if (!y) continue;
				z=fa[x];
				if (z){
					if (x==lc[z]) lc[z]=y;
					else rc[z]=y;
				}
				rc[x]=lc[y];
				lc[y]=x;
				fa[x]=y; fa[y]=z;
				if (rc[x]) fa[rc[x]]=x;
				if (rc[x]) rr[x]=rr[rc[x]];
				else rr[x]=id[x];
				ll[y]=ll[x];
				sum[x]=(sum[lc[x]]+sum[rc[x]]+key[x])%oo;
				sum[y]=(sum[lc[y]]+sum[rc[y]]+key[y])%oo;
				modify(1,1,n,id[x],sum[x]);
				modify(1,1,n,id[y],sum[y]);
			}
			else{
				printf("%I64d\n",query(1,1,n,ll[x],rr[x]));
			}
			// cout<<i<<endl;
			// for (int j=1;j<=n;j++) cout<<j<<' '<<sum[j]<<' '<<ll[j]<<' '<<rr[j]<<endl;
		}
	}
	return 0;
}