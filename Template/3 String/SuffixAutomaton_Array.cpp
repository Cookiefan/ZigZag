#include <bits/stdc++.h>
using namespace std;
#define maxn 100200
#define sgm 26

struct SAM{
	int fa[maxn<<1],len[maxn<<1];
	int ch[maxn<<1][sgm];
	int num, rot, n;
	int new_node(int x){
        fa[x]=-1;
        flag[x]=len[x]=0;
        for (int i=0;i<26;i++)
            ch[x][i]=-1;
        return x;
    }
    void init(){
        num=rot=new_node(0);
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
		n=strlen(s);
		for (int i=0;i<ll;i++){
			int w=s[i]-'a';
			//多串
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
		return now;
	}
	int match(char s[]){
        int now=rot, tmp=0, ans=0;
        int ll=strlen(s);
        for (int i=0;i<ll;i++){
            int w=s[i]-'a';
            if (ch[now][w]!=-1){
                now=ch[now][w];
                tmp++;
            }
            else{
                while (now!=-1&&ch[now][w]==-1)
                    now=fa[now];
                if (now!=-1){
                    tmp=len[now]+1;
                    now=ch[now][w];
                }
                else{
                    tmp=0;
                    now=rot;
                }
            }
            ans=max(ans,tmp);
        }
        return ans;
    }
	int pool[maxn<<1],q[maxn<<1];
	void topo(){
		memset(pool,0,sizeof(pool));
		for (int i=0;i<=num;i++) pool[len[i]]++;
		for (int i=1;i<=n;i++) pool[i]+=pool[i-1];
		for (int i=num;i>=0;i--) q[--pool[len[i]]]=i;
	}
	void show(){
		for (int i=0;i<=num;i++)
		{
			cout<<i<<": ";
			for (int w=0;w<26;w++)
				if (ch[i][w]!=-1)
					cout<<(char)('a'+w)<<"->"<<ch[i][w]<<", ";
			cout<<"fa->"<<fa[i];
			cout<<endl;
		}
	}
}sam;
// input:
// aabbabd
// output:
// 0: a->1, b->5, d->9, fa->-1
// 1: a->2, b->8, fa->0
// 2: b->3, fa->1
// 3: b->4, fa->8
// 4: a->6, fa->5
// 5: a->6, b->4, d->9, fa->0
// 6: b->7, fa->1
// 7: d->9, fa->8
// 8: b->4, d->9, fa->5
// 9: fa->0