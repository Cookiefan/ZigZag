//AC自动机
struct ACAM{
    int ch[maxn][27], v[maxn];
    int fail[maxn];
    int rot, num, now;
    void init(){
        rot=num=now=0;
        memset(ch[0],-1,sizeof(ch[0]));
        v[0]=0;
        //memset最好新建节点的时候写
    }
    int newnode(){
        num++;
        memset(ch[num],-1,sizeof(ch[num]));
        v[num]=0;
        return num;
    }
    void insert(int w){
        if (ch[now][w]==-1) ch[now][w]=newnode();
        now=ch[now][w];
    }
    void build(char s[]){
        now=rot;
        int n=strlen(s);
        for (int i=0;i<n;i++){
            insert(s[i]-'a');
        }
        v[now]++;
    }
    void connect(){
        queue<int> q;
        memset(fail,-1,sizeof(fail));
        fail[rot]=rot;
        for (int w=0;w<26;w++)
            if (ch[rot][w]==-1)
                ch[rot][w]=rot;
            else{
                fail[ch[rot][w]]=rot;
                q.push(ch[rot][w]);
            }
        while (!q.empty())
        {
            int x=q.front(); q.pop();
            for (int w=0;w<26;w++)
                if (ch[x][w]==-1)
                    ch[x][w]=ch[fail[x]][w];
                else
                {
                    int y=ch[x][w];
                    fail[y]=ch[fail[x]][w];
                    q.push(y);
                }
        }
    }
    int query(char s[]){
        now=rot;
        int n=strlen(s);
        int cnt=0;
        for (int i=0;i<n;i++){
            int w=s[i]-'a';
            now=ch[now][w];
            int tmp=now;
            while (tmp!=rot){
                cnt+=v[tmp];
                v[tmp]=0;
                tmp=fail[tmp];
            }
        }
        return cnt;
    }
    void show(){
        for (int i=0;i<=num;i++)
        {
            cout<<i<<": ";
            for (int w=0;w<26;w++)
                if (ch[i][w]!=rot)
                    cout<<(char)('a'+w)<<"->"<<ch[i][w]<<", ";
            cout<<"fa->"<<fail[i];
            cout<<' '<<v[i];
            cout<<endl;
        }
    }
}acam;
// input:
//5
// she
// he
// say
// shr
// her
// yasherhs
// output:
// 0: h->4, s->1, fa->0
// 1: a->6, h->2, s->1, fa->0
// 2: e->3, h->4, r->8, s->1, fa->4
// 3: h->4, r->9, s->1, fa->5
// 4: e->5, h->4, s->1, fa->0
// 5: h->4, r->9, s->1, fa->0
// 6: h->4, s->1, y->7, fa->0
// 7: h->4, s->1, fa->0
// 8: h->4, s->1, fa->0
// 9: h->4, s->1, fa->0
// 3