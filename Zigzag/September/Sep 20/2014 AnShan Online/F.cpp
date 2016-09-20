#include <bits/stdc++.h>
#define maxn 100200
#define inf 99999999
using namespace std;
int c[maxn][2], fa[maxn], size[maxn];
int key[maxn], fst[maxn], sec[maxn], cov[maxn], add[maxn], rev[maxn];
int fstsum[maxn], secsum[maxn];
int n,m;

typedef pair<int ,int> pii;
bool cmp(pii a, pii b)
{
	return a.first>b.first;
}
pii q[5];
//LCT
void update(int x)
{
	if (!x) return ;
	size[x]=size[c[x][0]]+size[c[x][1]]+1;
	int ms=0;
	q[ms++]=pii(key[x], 1);
	if (c[x][0]!=0)
	{
		q[ms++]=pii(fst[c[x][0]], fstsum[c[x][0]]);
		if (sec[c[x][0]]!=fst[c[x][0]])
			q[ms++]=pii(sec[c[x][0]], secsum[c[x][0]]);
	}
	if (c[x][1]!=0)
	{
		q[ms++]=pii(fst[c[x][1]], fstsum[c[x][1]]);
		if (sec[c[x][1]]!=fst[c[x][1]])
			q[ms++]=pii(sec[c[x][1]], secsum[c[x][1]]);
	}
	sort(q, q+ms, cmp);
	fst[x]=sec[x]=q[0].first;
	for (int i=0;i<ms;i++)
		if (q[i].first<sec[x])
		{
			sec[x]=q[i].first;
			break;
		}
	//for (int i=0;i<ms;i++) cout<<q[i].first<<' '; cout<<endl;
	fstsum[x]=0;
	secsum[x]=0;
	for (int i=0;i<ms;i++)
	{
		if (q[i].first==fst[x]) fstsum[x]+=q[i].second;
		if (q[i].first==sec[x]) secsum[x]+=q[i].second;
	}
}

void reverse(int x)
{
	if (!x) return ;
	swap(c[x][0], c[x][1]);
	rev[x]^=1;
}

void addvalue(int x, int ad)
{
	if (!x) return ;
	key[x]+=ad;
	fst[x]+=ad;
	sec[x]+=ad;
	if (cov[x]!=-inf) cov[x]+=ad;
	else add[x]+=ad;
}

void cover(int x, int cv)
{
	if (!x) return ;
	key[x]=fst[x]=sec[x]=cv;
	fstsum[x]=secsum[x]=size[x];
	cov[x]=cv;
	add[x]=0;
}

void down(int x)
{
	if (rev[x])
	{
		reverse(c[x][0]);
		reverse(c[x][1]);
		rev[x]=0;
	}
	if (cov[x]!=-inf)
	{
		cover(c[x][0], cov[x]);
		cover(c[x][1], cov[x]);
		cov[x]=-inf;
	}
	if (add[x])
	{
		addvalue(c[x][0], add[x]);
		addvalue(c[x][1], add[x]);
		add[x]=0;
	}	
}

bool is_root(int x)
{
	return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}

void relax(int x)
{
	if (!is_root(x)) relax(fa[x]);
	down(x);
}

void zigzag(int x)
{
	int y=fa[x], z=fa[y];
	int p=(c[y][1]==x), q=p^1;
	if (!is_root(y)) c[z][c[z][0]!=y]=x;
	fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
	c[y][p]=c[x][q]; c[x][q]=y;
	update(y);
}

void splay(int x)
{
	relax(x);
	while (!is_root(x))
	{
		int y=fa[x], z=fa[y];
		if (!is_root(y))
			((c[y][0]==x) ^ (c[z][0]==y))?zigzag(x):zigzag(y);
		zigzag(x);
	}
	update(x);
}

int access(int x)
{
	int y=0;
	for (; x; y=x, x=fa[x])
	{
		splay(x);
		c[x][1]=y;
		update(x);
	}
	return y;
}

int root(int x)
{
	while (fa[x]) x=fa[x];
	return x;
}

void make_root(int x)
{
	access(x);
	splay(x);
	reverse(x);
}

void split(int x, int y)
{
	make_root(y);
	access(x);
	splay(x);
}

void link(int x, int y)
{
	make_root(x);
	fa[x]=y;
}

void cut(int x, int y)
{
	split(y, x);
	c[y][0]=fa[x]=0;
}

// void write(int x)
// {
// 	cout<<"id: "<<x<<endl;
// 	update(x);
// 	cout<<fa[x]<<' '<<c[x][0]<<' '<<c[x][1]<<' '<<key[x]<<' '<<fst[x]<<' '<<sec[x]<<endl;
// }

// void solve(int x, int y, int z)
// {
// 	access(x);
// 	int lca=access(y);
// 	splay(x);
// 	change(c[lca][1], z);
// 	key[lca]=z;
// 	if (x!=lca) change(x, z);
// }

int main()
{
	//freopen("F.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		memset(fa,0,sizeof(fa));
		memset(c,0,sizeof(c));
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&key[i]);
			size[i]=1;
			fst[i]=sec[i]=key[i];
			fstsum[i]=secsum[i]=1;
			add[i]=0;
			cov[i]=-inf;
			rev[i]=0;
		}
		int x, y, z, u, v, sign;
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			link(x, y);
		}
		printf("Case #%d:\n",o);
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&sign);
			if (sign==1)
			{
				scanf("%d%d%d%d",&u,&v,&x,&y);
				cut(u, v);
				link(x, y);
			}
			else if (sign==2)
			{
				scanf("%d%d%d",&x,&y,&z);
				split(x, y);
				cover(x, z);
			}
			else if (sign==3)
			{
				scanf("%d%d%d",&x,&y,&z);
				split(x, y);
				addvalue(x, z);
			}
			else if (sign==4)
			{
				scanf("%d%d",&x,&y);
				split(x, y);
				//for (int i=1;i<=n;i++) write(i);
				if (fst[x]==sec[x])
					printf("ALL SAME\n");
				else
					printf("%d %d\n",sec[x], secsum[x]);
			}
		}
	}
	return 0;
}