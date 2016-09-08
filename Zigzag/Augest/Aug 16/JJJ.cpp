#include <bits/stdc++.h>
#define inf 2147483647
#define maxn 100200
using namespace std;
struct node
{
    node *pre,*ch[26];
    int mx;
    void clear()
    {
        for (int i=0;i<26;i++) ch[i]=NULL;
        pre=NULL;
        mx=0;
    }
}sam[2*maxn],*rot,*now,*r[2*maxn];
char s[maxn];
int n,m,num;

inline void insert(int w)
{
    node *p=now,*np=&sam[++num];
    np->mx=p->mx+1;
    while (p!=NULL && p->ch[w]==NULL) p->ch[w]=np,p=p->pre;
    if (p==NULL) np->pre=rot;
    else
    {
        node *q=p->ch[w];
        if (q->mx==p->mx+1) np->pre=q;
        else
        {
            node *nq=&sam[++num];
            *nq=*q;
            nq->mx=p->mx+1;
            np->pre=q->pre=nq;
            while (p!=NULL && p->ch[w]==q) p->ch[w]=nq,p=p->pre;
        }
    }
    now=np;
}  

inline int query(char *s)
{
    now=rot;
    int len=strlen(s);
    for (int i=0;i<len;i++)
    {
        int w=s[i]-'a';
        if (now->ch[w]==NULL) return 0;
        else now=now->ch[w];
    }
    return (now->mx)-(now->pre->mx);
}

int main()
{
    //cout<<sizeof(sam)/1024/1024<<endl;
    //freopen("J.in","r",stdin);
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {
        scanf("%d%d",&n,&m);
        rot=&sam[num=1];
        for (int i=1;i<=n;i++)
        {
            scanf(" %s",s);
            int len=strlen(s);
            now=rot;
            for (int j=0;j<len;j++)
            {
                int w=s[j]-'a';
                if (now->ch[w]!=NULL && now->ch[w]->mx==j+1) now=now->ch[w];
                else insert(w);
            }
        }

        printf("Case #%d:\n",o);

        for (int i=1;i<=m;i++)
        {
            scanf(" %s",s);
            printf("%d\n",query(s));
        }
        for (int i=1;i<=num;i++) sam[i].clear();
    }
    return 0;
}