//后缀自动机
struct node
{
    node *pre,*ch[27];
    int mx;
    node(){
    	mx=0;
    	pre=NULL;
    	for (int i=0;i<=26;i++) ch[i]=0;
    }
}*rot,*now,*que[maxn];

inline void ins(int w)
{
	node *p=now,*np=&rot[++num];
	np->mx=p->mx+1;
	while (p!=NULL && p->ch[w]==NULL) p->ch[w]=np,p=p->pre;
	if (p==NULL) np->pre=rot;
	else
	{
		node *q=p->ch[w];
		if (q->mx==p->mx+1) np->pre=q;
		else
		{
			node *nq=&rot[++num];
			*nq=*q;
			nq->mx=p->mx+1;
			np->pre=q->pre=nq;
			while (p!=NULL && p->ch[w]==q) p->ch[w]=nq,p=p->pre;
		}
	}
	now=np;
}

inline void build(char *s)
{
	rot=new node[maxn];
	now=&rot[num=0];
	int n=strlen(s);
	for (int i=0;i<n;i++) ins(s[i]-'a');
}

void clear()
{
	delete [] rot;
}

inline void tong_sort()
{
	for (int i=1;i<n;i++) tong[i]=0;
	for (int i=0;i<=num;i++) tong[rot[i].mx]++;
	for (int i=1;i<=n;i++) tong[i]+=tong[i-1];
	for (int i=num;i>=0;i--) que[--tong[rot[i].mx]]=&rot[i];
}