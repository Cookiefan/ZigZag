#include <bits/stdc++.h>
using namespace std;
#define maxn 3000000
#define sgm 26
typedef long long LL;
struct LCT_SAM{
	//LCT
	int fa[maxn<<1],c[maxn<<1][2];
	int key[maxn<<1],add[maxn<<1];
	void addit(int x, int z){
		key[x]+=z;
		add[x]+=z;
	}
	void down(int x){
		if (add[x]){
			addit(c[x][0], add[x]);
			addit(c[x][1], add[x]);
			add[x]=0;
		}
	}
	bool is_root(int x){
		return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
	}
	void relax(int x){
		if (!is_root(x)) relax(fa[x]);
		down(x);
	}
	void zigzag(int x){
		int y=fa[x], z=fa[y];
		int p=(c[y][1]==x),q=p^1;
		if (!is_root(y)) c[z][c[z][0]!=y]=x;
		fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
		c[y][p]=c[x][q]; c[x][q]=y;
	}
	void splay(int x){
		relax(x);
		while (!is_root(x)){
			int y=fa[x],z=fa[y];
			if (!is_root(y)){
				if ((c[y][0]==x)^(c[z][0]==y))
					zigzag(x);
				else
					zigzag(y);
			}
			zigzag(x);
		}
	}
	int access(int x){
		int y=0;
		for (;x;y=x,x=fa[x]){
			splay(x);
			c[x][1]=y;
		}
		return y;
	}
	int root(int x){
		while (fa[x]) x=fa[x];
		return x;
	}
	void link(int x, int y){
		if (!y) return ;
		fa[x]=y;
		access(y);
		splay(y);
		addit(y, key[x]);
	}
	void cut(int x, int y){
		if (!y) return ;
		access(y);
		splay(y);
		addit(y,-key[x]);
		c[y][0]=fa[x]=0;
	}
	//SAM
	int len[maxn<<1];
	int ch[maxn<<1][sgm];
	int now, num, rot;
	void init(){
		now=num=rot=1;
		memset(fa,0,sizeof(fa));
		memset(c,0,sizeof(c));
		memset(ch,0,sizeof(ch));
		memset(len,0,sizeof(len));
		memset(key,0,sizeof(key));
		memset(add,0,sizeof(add));
	}
	int insert(int p, int w){
		int np=++num;
		len[np]=len[p]+1;
		addit(np, 1);// key[np]=1;
		//cout<<p<<' '<<w<<endl;
		while (p && !ch[p][w])
			ch[p][w]=np,p=fa[p];
		if (!p) link(np,rot);//fa[np]=rot;
		else{
			int q=ch[p][w];
			if (len[q]==len[p]+1)
				link(np, q);// fa[np]=q;
			else{
				int nq=++num;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				link(nq, fa[q]);//fa[nq]=fa[q];
				len[nq]=len[p]+1;
				link(np, nq);//fa[np]=nq;
				cut(q, fa[q]); link(q, nq);//fa[q]=nq;
				while (p && ch[p][w]==q)
					ch[p][w]=nq,p=fa[p];
			}
		}
		return np;
	}
	void build(char s[]){
		int n=strlen(s);
		for (int i=0;i<n;i++){
			int w=s[i]-'a';
            now=insert(now,w);
		}
		cout<<ch[rot][3]<<endl;
	}
	int query(char s[]){
		int x=rot;
		int ll=strlen(s);
		for (int i=0;i<ll;i++){
			int w=s[i]-'a';
			if (!ch[x][w]) return 0;
			else x=ch[x][w];
		}
		access(x);
		return key[x];
	}
}sam;

int m;
char s[maxn];

int main()
{
	freopen("B.in","r",stdin);
	scanf("%d",&m);
	scanf(" %s",s);
	sam.init();
	sam.build(s);
	for (int i=1;i<=sam.num;i++)
	{
		cout<<i<<": ";
		for (int w=0;w<26;w++)
			if (sam.ch[i][w])
				cout<<(char)('a'+w)<<"->"<<sam.ch[i][w]<<", ";
		cout<<"fa: "<<sam.fa[i];
		cout<<endl;
	}

	for (int i=1;i<=m;i++){
		scanf(" %s",s);
		if (s[0]=='A'){
			scanf(" %s",s);
			sam.build(s);
		}
		else{
			scanf(" %s",s);
			printf("%d\n",sam.query(s));
		}
	}
	return 0;
}