#include <bits/stdc++.h>
using namespace std;
#define maxn 200200
int L[maxn];
typedef map<int,int>::iterator mit;
struct SAM{
    int fa[maxn<<2], len[maxn<<2];
    map<int,int> flag[maxn<<2];
    int ch[maxn<<2][26];
    int ed[maxn];
    int num, rot;
    void init(){
        num=rot=0;
        fa[num]=-1;
        len[num]=0;
        flag[num].clear();
        for (int i=0;i<26;i++)
            ch[rot][i]=-1;
    }
    int new_node(){
        ++num;
        fa[num]=-1;
        len[num]=0;
        flag[num].clear();
        for (int i=0;i<26;i++)
            ch[num][i]=-1;
        return num;
    }
    int ins(int p, int w){
        int np=new_node();
        len[np]=len[p]+1;
        while (p!=-1&&ch[p][w]==-1)
            ch[p][w]=np, p=fa[p];
        if (p==-1) fa[np]=rot;
        else{
            int q=ch[p][w];
            if (len[q]==len[p]+1)
                fa[np]=q;
            else{
                int nq=new_node();
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                fa[nq]=fa[q];
                len[nq]=len[p]+1;
                fa[np]=fa[q]=nq;
                while(p!=-1&&ch[p][w]==q)
                    ch[p][w]=nq, p=fa[p];
            }
        }
        return np;
    }
    void build(char s[], int id){
        int now=rot;
        int ll=strlen(s);
        for (int i=0;i<ll;i++){
            int w=s[i]-'a';
            if (ch[now][w]!=-1&&len[ch[now][w]]==i+1)
                now=ch[now][w];
            else
                now=ins(now, w);
        }
        ed[id]=now;
        if (!flag[now].count(ll)) flag[now][ll]=0;
        flag[now][ll]++;
    }
    void change(int w, int id){
        int now=ed[id];
        flag[now][L[id]]--;
        if (flag[now][L[id]]==0) flag[now].erase(L[id]);
        now=ins(now, w);
        L[id]++;
        if (!flag[now].count(L[id])) flag[now][L[id]]=0;
        flag[now][L[id]]++;
        ed[id]=now;
    }
    int query(char s[]){
        int now=rot, tmp=0;
        int ll=strlen(s);
        for (int i=0;i<ll;i++){
            int w=s[i]-'a';
            //cout<<now<<' '<<w<<endl
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
            if (flag[now].size()&&tmp>=len[now])
                return 1;
        }
        return 0;
    }
    void show(){
        for (int i=0;i<=num;i++){
            cout<<i<<": ";
            for (int w=0;w<26;w++)
                if (ch[i][w]!=-1)
                    cout<<(char)('a'+w)<<"->"<<ch[i][w]<<", ";
            cout<<"fa->"<<fa[i]<<"  len->"<<len[i];
            cout<<"  flag: ";
            for (mit t=flag[i].begin();t!=flag[i].end();t++)
                cout<<t->first<<' ';
            cout<<endl;
        }
    }
}sam;

int n,m,last;
char s[maxn];

int main()
{
    //freopen("A.in","r",stdin);
    scanf("%d%d",&n,&m);
    sam.init();
    for (int i=0;i<n;i++){
        scanf(" %s",s);
        L[i]=strlen(s);
        sam.build(s, i);
    }
    //sam.show();
    last=0;
    int x, y, sign;
    for (int i=0;i<m;i++){
        scanf("%d",&sign);
        if (sign==1){
            scanf(" %s",s);
            int ll=strlen(s);
            for(int j=0;j<ll;j++)
                s[j]='a'+(s[j]-'a'+last)%26;
            int tmp=sam.query(s);
            if (tmp) last=i;
            printf(tmp?"YES\n":"NO\n");
        }
        else{
            scanf("%d%d",&x,&y);
            x=(x+last)%n;
            y=(y+last)%26;
            sam.change(y, x);
        }
    }
    return 0;
}