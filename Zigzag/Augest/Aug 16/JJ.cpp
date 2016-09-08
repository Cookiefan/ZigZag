#include <bits/stdc++.h>
#define inf 2147483647
#define maxn 100200
using namespace std;
struct node
{
    node *pre,*ch[26];
    int mx,v,f;
    void clear()
    {
        mx=v=f=0;
        for (int i=0;i<26;i++) ch[i]=NULL;
        pre=NULL;
    }
}sam[2*maxn],*rot,*now,*r[2*maxn];
char s[maxn], ss[maxn];
int n,m,num,tot;
int t[maxn];

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

inline node* query(char *s)
{
    now=rot;
    int len=strlen(s);
    for (int i=0;i<len;i++)
    {
        int w=s[i]-'a';
        if (now->ch[w]==NULL) return NULL;
        else now=now->ch[w];
    }
    return now;
}

int main()
{
    //freopen("J.in","r",stdin);
    //cout<<sizeof(sam)/1024/1024<<endl;
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {
        scanf("%d%d",&n,&m);
        tot=0;
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
            now=rot;
            for (int j=0;j<len;j++)
            {
                int w=s[j]-'a';
                now=now->ch[w];
                now->v++;
            }
            tot+=len;
        }

        for (int i=0;i<=tot;i++) t[i]=0;
        for (int i=1;i<=num;i++) t[sam[i].mx]++;
        for (int i=1;i<=tot;i++) t[i]+=t[i-1];
        for (int i=num;i>=1;i--) r[t[sam[i].mx]--]=&sam[i];

        for (int i=num;i>=2;i--) r[i]->pre->v+=r[i]->v;

        printf("Case #%d:\n",o);

        for (int i=1;i<=m;i++)
        {
            scanf(" %s",s);
            int len=strlen(s);
            node *tmp=query(s);
            if (tmp==NULL)
            {
                printf("%d\n",0);
                continue;
            }
            int h=tmp->mx;
            int l=1, r=len,ans=len;
            while (l<=r)
            {
                int mid=(l+r)>>1;
                strncpy(ss, s+len-mid, mid+1);
                if (query(ss)->v==tmp->v)
                    
                {
                    ans=mid;
                    r=mid-1;
                }
                else
                    l=mid+1;
            }
            printf("%d\n",h-ans+1);
        }
        for (int i=1;i<=num;i++) sam[i].clear();
    }
    return 0;
}
