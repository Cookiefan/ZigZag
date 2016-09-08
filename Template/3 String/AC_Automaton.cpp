//AC自动机
void insert(int w)
{
    if (!ch[now][w]) ch[now][w]=++num;
    fa[ch[now][w]]=now;
    now=ch[now][w];
}

void add(int x,int y)
{
    e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

void build()
{
    int head=0,tail=1;
    q[1]=rot;
    while (head<tail)
    {
        int p=q[++head];
        for (int w=0;w<26;w++)
            if (ch[p][w])
            {
                int tmp=ch[p][w];
                int j=p;
                if (j==rot) fail[tmp]=rot;
                else
                {
                    j=fail[j];
                    while (j&&ch[j][w]==0) j=fail[j];
                    if (ch[j][w]) fail[tmp]=ch[j][w];
                    else fail[tmp]=rot;
                }
                add(fail[tmp],tmp);
                q[++tail]=tmp;
            }
    }
}