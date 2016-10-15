#include <bits/stdc++.h>
using namespace std;
#define maxn 500200
#define sgm 26
typedef long long LL;

struct SAM{
	int fa[maxn<<1],len[maxn<<1];
	int ch[maxn<<1][sgm];
	LL sum[maxn<<1],f[maxn<<1];
	int n, num, rot;
	void init(){
		num=rot=0;
		memset(fa,-1,sizeof(fa));
		memset(ch,-1,sizeof(ch));
		memset(len,0,sizeof(len));
		memset(sum,0,sizeof(sum));
		memset(f,0,sizeof(f));
	}
	int insert(int p, int w){
		int np=++num;
		len[np]=len[p]+1;
		f[np]=sum[np]=1;
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
		n=strlen(s);
		for (int i=0;i<n;i++){
			int w=s[i]-'a';
			if (ch[now][w]!=-1&&len[ch[now][w]]==i+1)
				now=ch[now][w];
            else
            	now=insert(now,w);
		}
	}
	int pool[maxn<<1],q[maxn<<1];
	LL topo(){
		LL tmp=0;
		memset(pool,0,sizeof(pool));
		for (int i=0;i<=num;i++) pool[len[i]]++;
		for (int i=1;i<=n;i++) pool[i]+=pool[i-1];
		for (int i=num;i>=0;i--) q[--pool[len[i]]]=i;
		for (int i=num;i>=0;i--){
			int x=q[i];
			sum[fa[x]]+=sum[x];
		}
		for (int i=num;i>=1;i--){
			int x=q[i];
			tmp+=(sum[fa[x]]-sum[x]+f[fa[x]])*sum[x]*len[fa[x]];
		}
		return tmp;
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

char s[maxn];
int n;
LL ans;

int main()
{
	//freopen("A.in","r",stdin);
	sam.init();
	scanf(" %s",s);
	sam.build(s);
	sam.show();
	n=strlen(s);
	reverse(s,s+n);
	sam.build(s);
	ans=(LL)n*(n+1)/2*(n-1);
	LL tmp=sam.topo();
	//cout<<ans<<' '<<tmp<<endl;
	printf("%lld\n",ans-tmp);
    return 0;
}