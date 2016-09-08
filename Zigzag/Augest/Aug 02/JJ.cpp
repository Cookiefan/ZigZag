#include <bits/stdc++.h>
#define maxn 120000
using namespace std;

int c[maxn][30], last[maxn];
int n, m, num, tot;

struct treenode
{
	int lc, rc;
	int s;
	node(){s=lc=rc=0;}
}tree[50*maxn];
int rot[maxn];

chair_clear()
{
	tot=0;
}

void chair_add(int &p, int l, int r, int pos, int z)
{
	tree[++tot]=tree[p];
	tree[tot].s=tree[p].s+z;
	p=tot;
	if (l==r) return ;
	int mid=(l+r)>>1;
	if (pos<=mid) chair_add(tree[p].lc, l, mid, pos, z);
	else chair_add(tree[p].rc, mid+1, r, pos, z);
}

int chair_query(int x, int l, int r, int ll , int rr)
{
	if (ll<=l && r<=rr) return tree[x].s;
	int mid=(l+r)>>1, tmp=0;
	if (ll<=mid) tmp+=chair_query(tree[x].lc, l, mid, ll, rr);
	if (rr>mid) tmp+=chair_query(tree[x].rc, mid+1, r, ll, rr);
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
	int cur=rot[st-1];
	for (int i=0;i<ls;i++)
	{
		int w=s[i]-'a';
		if (c[now][w]==-1)
			c[now][w]=++num;
		now=c[now][w];
		if (last[now]!=-1)
			chair_add(cur, 1, n, last[now], -1);
		chair_add(cur, 1, n, st, 1);
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
		rot[0]=0;
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