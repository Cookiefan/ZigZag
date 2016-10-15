struct LCT{
	int fa[maxn],c[maxn][2];
	int key[maxn],add[maxn];
	void init(){
		memset(key, 0, sizeof(key));
		memset(add, 0, sizeof(add));
		memset(c, 0, sizeof(c));
		memset(fa, 0, sizeof(fa));
	}
	void addit(int x, int z){
		if (!x) return;
		key[x]+=z;
		add[x]+=z;
	}
	void down(int x){
		if (!x) return ;
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
	void access(int x){
		for (int y=0;x;y=x,x=fa[x]){
			splay(x);
			c[x][1]=y;
		}
	}
	int root(int x){
		while (fa[x]) x=fa[x];
		return x;
	}
	void link(int x, int y){
		fa[x]=y;
		access(y);
		splay(y);
		addit(y, key[x]);
	}
	void cut(int x){
		access(x);
		splay(x);
		addit(c[x][0], -key[x]);
		fa[c[x][0]]=0; c[x][0]=0;
	}
}lct;
struct SAM{	
	//SAM
	int len[maxn];
	int fa[maxn], ch[maxn][sgm];
	int now, num, rot;
	void init(){
		now=num=rot=1;
		memset(fa,0,sizeof(fa));
		memset(ch,0,sizeof(ch));
		memset(len,0,sizeof(len));
	}
	int insert(int p, int w){
		int np=++num;
		len[np]=len[p]+1;
		lct.key[np]=1;
		//cout<<p<<' '<<w<<endl;
		while (p && !ch[p][w])
			ch[p][w]=np,p=fa[p];
		if (!p) lct.link(np,fa[np]=rot);//fa[np]=rot;
		else{
			int q=ch[p][w];
			if (len[q]==len[p]+1)
				lct.link(np, fa[np]=q);// fa[np]=q;
			else{
				int nq=++num;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				lct.link(nq, fa[nq]=fa[q]);//fa[nq]=fa[q];
				len[nq]=len[p]+1;
				lct.link(np, fa[np]=nq);//fa[np]=nq;
				lct.cut(q); lct.link(q, fa[q]=nq);//fa[q]=nq;
				while (p && ch[p][w]==q)
					ch[p][w]=nq,p=fa[p];
			}
		}
		return np;
	}
	void build(char s[]){
		int n=strlen(s);
		for (int i=0;i<n;i++){
			int w=s[i]-'A';
            now=insert(now,w);
		}
	}
	int query(char s[]){
		int x=rot;
		int n=strlen(s);
		for (int i=0;i<n;i++){
			int w=s[i]-'A';
			if (!ch[x][w]) return 0;
			else x=ch[x][w];
		}
		if (x==rot) return 0;
		lct.access(x);
		lct.splay(x);
		return lct.key[x];
	}
	void show(){
		for (int i=1;i<=num;i++)
		{
			cout<<i<<": "<<lct.key[i]<<' ';
			for (int w=0;w<26;w++)
				if (ch[i][w])
					cout<<(char)('A'+w)<<"->"<<ch[i][w]<<", ";
			cout<<"fa->"<<fa[i];
			cout<<endl;
		}
	}
}sam;