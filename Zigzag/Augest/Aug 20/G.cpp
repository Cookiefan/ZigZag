#include <bits/stdc++.h>
#define inf 2147483647
#define maxn 100200
using namespace std;

typedef pair<int,int> pii;
struct node
{
    node *pre,*ch[26];
    int mx, v;
    void clear()
    {
        for (int i=0;i<26;i++) ch[i]=NULL;
        pre=NULL;
        mx=v=0;
    }
}sam[2*maxn],*rot,*now,*r[2*maxn];
char s[maxn];
int t[2*maxn];
int n,m,num;
vector<pii> q;

inline void insert(int w)
{
    node *p=now,*np=&sam[++num];
    np->mx=p->mx+1; np->v=np->mx;
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

inline pii query(int st)
{
    now=rot;
    pii ans=pii(-1, s[st]);
    for (int i=st;i<n;i++)
    {
        int w=s[i]-'a';
        if (now->ch[w]==NULL) return ans;
        else
        {
        	now=now->ch[w];
        	//cout<<"i: "<<i<<' '<<now->v<<endl;
        	if (now->v<i+1)
        		ans=pii(i-st+1, now->v-i+st-1);
        	else
        		return ans;
        }
    }
    return ans;
}

int main()
{
    int Case;
    scanf("%d",&Case);
    for (int o=1;o<=Case;o++)
    {
    	scanf(" %s",s);
    	n=strlen(s);
    	now=rot=&sam[num=1];
    	for (int i=0;i<n;i++) insert(s[i]-'a');

    	for (int i=0;i<=n;i++) t[i]=0;
        for (int i=1;i<=num;i++) t[sam[i].mx]++;
        for (int i=1;i<=n;i++) t[i]+=t[i-1];
        for (int i=num;i>=1;i--) r[t[sam[i].mx]--]=&sam[i];

        for (int i=num;i>=2;i--) r[i]->pre->v=min(r[i]->pre->v, r[i]->v);

        printf("Case #%d:\n",o);
    	printf("%d %d\n",-1, s[0]);
    	int i=1;
    	while (i<n)
    	{
    		pii tmp=query(i);
            printf("%d %d\n",tmp.first, tmp.second);
    		if (tmp.first==-1)
    			i++;
    		else
    			i+=tmp.first;
    	}
       
        for (int i=1;i<=num;i++) sam[i].clear();
    }
    return 0;
}