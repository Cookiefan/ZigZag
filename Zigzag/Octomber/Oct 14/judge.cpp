#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
typedef long long ll;  
const int maxn=1000010;  
using namespace std;  
int n;char s[maxn];ll ans;  
  
struct Tsam{  
    int dis[maxn],fa[maxn],ch[maxn][26],ri[maxn],sum[maxn],last,root,tot;  
    int su[maxn],tmp[maxn];  
    void init(){last=root=tot=1;}  
    int newnode(int v){dis[++tot]=v;return tot;}  
    void add(int x){  
        int p=last,np=newnode(dis[p]+1);  
        ri[np]=sum[np]=1,last=np;  
        for (;p&&!ch[p][x];p=fa[p]) ch[p][x]=np;  
        if (!p) fa[np]=root;  
        else{  
            int q=ch[p][x];  
            if (dis[q]==dis[p]+1) fa[np]=q;  
            else{  
                int nq=newnode(dis[p]+1);  
                memcpy(ch[nq],ch[q],sizeof(ch[q]));  
                fa[nq]=fa[q];  
                fa[q]=fa[np]=nq;  
                for (;ch[p][x]==q;p=fa[p]) ch[p][x]=nq;  
            }  
        }  
    }  
    void Tsort(){  
        for (int i=1;i<=tot;i++) su[dis[i]]++;  
        for (int i=1;i<=n;i++) su[i]+=su[i-1];  
        for (int i=tot;i;i--) tmp[su[dis[i]]--]=i;  
    }  
    void treeDP(){  
        Tsort();  
        for (int i=tot;i;i--){  
            int x=tmp[i];  
            ri[fa[x]]+=ri[x];  
        }  
        for (int i=tot;i;i--){  
            int x=tmp[i];  
            ans+=1ll*sum[fa[x]]*ri[x]*dis[fa[x]];  
            sum[fa[x]]+=ri[x];  
        }  
    }  
}T;  
  
int main(){  
    scanf("%s",s+1),n=strlen(s+1),T.init();  
    for (int i=n;i;i--) T.add(s[i]-'a');  
    T.treeDP();  
    printf("%lld\n",1ll*(n+1)*n/2*(n-1)-ans*2);  
    return 0;  
}  