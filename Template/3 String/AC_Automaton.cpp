//AC自动机
int ch[maxn][27], v[maxn];
int fail[maxn];
int rot, num, now, n;
char s[maxn];

void ins(int w)
{
    if (ch[now][w]==-1) ch[now][w]=++num;
    now=ch[now][w];
}

void build()
{
    queue<int> q;
    memset(fail,0,sizeof(fail));
    for (int w=0;w<26;w++)
        if (ch[rot][w]==-1)
            ch[0][w]=rot;
        else
            q.push(ch[0][w]);
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
