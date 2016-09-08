#include <bits/stdc++.h>
#define maxn 100002
using namespace std;

int c[maxn][27], last[maxn];
int n, m, num, tot;

struct treenode
{
	treenode *lc, *rc;
	int s;
	node(){s=0;}
}*rot[maxn],*tree[30*maxn];

chair_clear()
{
	for (int i=0;i<=tot;i++) delete tree[i];
	tot=0;
}

treenode* chair_build(int l, int r)
{
	tree[++tot]=new treenode();
	treenode *x=tree[tot];
	if (l==r) return x;
	int mid=(l+r)>>1;
	x->lc=chair_build(l, mid);
	x->rc=chair_build(mid+1, r);
	return x;
}

treenode* chair_add(treenode *p, int l, int r, int pos, int z)
{
	tree[++tot]=new treenode();
	treenode *x=tree[tot];
	x->lc=p->lc; x->rc=p->rc;
	x->s=p->s+z;
	if (l==r) return x;
	int mid=(l+r)>>1;
	if (pos<=mid) x->lc=chair_add(p->lc, l, mid, pos, z);
	else x->rc=chair_add(p->rc, mid+1, r, pos, z);
	return x;
}

int chair_query(treenode *x, int l, int r, int ll , int rr)
{
	if (ll<=l && r<=rr) return x->s;
	int mid=(l+r)>>1, tmp=0;
	if (ll<=mid) tmp+=chair_query(x->lc, l, mid, ll, rr);
	if (rr>mid) tmp+=chair_query(x->rc, mid+1, r, ll, rr);
	return tmp;
}

void trie_clear()
{
	num=0;
	memset(last,-1,sizeof(last));
	memset(c,-1,sizeof(c));
}

void trie_add(string s, int st)
{
	int ls=s.length(), now=0;
	treenode* cur=rot[st-1];
	for (int i=0;i<ls;i++)
	{
		int w=s[i]-'a';
		if (c[now][w]==-1)
			c[now][w]=++num;
		now=c[now][w];
		if (last[now]!=-1)
			cur=chair_add(cur, 1, n, last[now], -1);
		cur=chair_add(cur, 1, n, st, 1);
		last[now]=st;
	}
	rot[st]=cur;
}

string s;

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		chair_clear();
		rot[0]=chair_build(1, n);
		trie_clear();
		for (int i=1;i<=n;i++)
		{
			cin>>s;
			trie_add(s, i);
		}
		int l, r;
		scanf("%d",&m);
		int ans=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&l, &r);
			l=(ans+l)%n+1;
			r=(ans+r)%n+1;
			if (l>r) swap(l,r);
			printf("%d\n",ans=chair_query(rot[r], 1, n, l, r));
		}
	}
	return 0;
}