
struct SAM{
	int fa[maxn<<1],len[maxn<<1];
	int ch[maxn<<1][sgm];
	int num, rot;
	void init(){
		num=rot=0;
		memset(fa,-1,sizeof(fa));
		memset(ch,-1,sizeof(ch));
		memset(len,0,sizeof(len));
	}
	int insert(int p, int w){
		int np=++num;
		len[np]=len[p]+1;
		while (p!=-1&&ch[p][w]==-1)
			ch[p][w]=np,p=fa[p];
		if (p==-1) fa[np]=rot;
		else{
			int q=ch[p][w];
			if (len[q]==len[p]+1)
				fa[np]=q;
			else{
				int nq=++num;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q];
				len[nq]=len[p]+1;
				fa[np]=fa[q]=nq;
				while (p!=-1&&ch[p][w]==q)
					ch[p][w]=nq,p=fa[p];
			}
		}
		return np;
	}
	void build(char s[]){
		int now=rot;
		int ll=strlen(s);
		for (int i=0;i<ll;i++){
			int w=s[i]-'a';
			if (ch[now][w]!=-1&&len[ch[now][w]]==i+1)
				now=ch[now][w];
            else
            	now=insert(now,w);
		}
	}
	int query(char s[]){
		int now=rot;
		int ll=strlen(s);
		for (int i=0;i<ll;i++){
			int w=s[i]-'a';
			if (ch[now][w]==-1) return 0;
			else now=ch[now][w];
		}
		return len[now]-len[fa[now]];
	}
}sam;
