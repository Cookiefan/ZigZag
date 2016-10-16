#include <bits/stdc++.h>
#define maxn 24000
#define high 1000002
using namespace std;
struct query
{
    int x,y,cur,tp,s;
}q[maxn],q1[maxn],q2[maxn];
int a[maxn],ans[maxn],tmp[maxn];
int n,m,num,cnt;
struct bit
{
    int b[maxn];
    void add(int x,int z)
    {
        for (int i=x;i<=n;i+=(i&-i)) b[i]+=z;
    }
    int ask(int x)
    {
        int tmp=0;
        for (int i=x;i>0;i-=(i&-i)) tmp+=b[i];
        return tmp;
    }
}t;
set<int> s[high];
set<int>::iterator p;
//set是颜色库，用来存储同种颜色的位置

void divide(int head,int tail,int l,int r)
{
    if (head>tail) return;
    if (l==r)
    {
        for (int i=head;i<=tail;i++)
            if (q[i].tp==3) ans[q[i].s]=q[i].cur;
        return ;
    }
    int mid=(l+r)>>1;
    for (int i=head;i<=tail;i++)
    {
        if (q[i].tp==1&&q[i].y<=mid) t.add(q[i].x,1);
        else
        if (q[i].tp==2&&q[i].y<=mid) t.add(q[i].x,-1);
        else
        if (q[i].tp==3) tmp[i]=t.ask(q[i].y)-t.ask(q[i].x-1);
    }
    for (int i=head;i<=tail;i++) 
    {
        if (q[i].tp==1&&q[i].y<=mid) t.add(q[i].x,-1);
        else
        if (q[i].tp==2&&q[i].y<=mid) t.add(q[i].x,1);
    }
    int l1=0,l2=0;
    for (int i=head;i<=tail;i++)
    {
        if (q[i].tp==3)
            if (q[i].x<=mid) q1[++l1]=q[i];
            else 
            {
                q[i].cur+=tmp[i];
                q2[++l2]=q[i];
            }
        else
            if (q[i].y<=mid) q1[++l1]=q[i];
            else q2[++l2]=q[i];
    }
    for (int i=1;i<=l1;i++) q[head+i-1]=q1[i];
    for (int i=1;i<=l2;i++) q[head+l1+i-1]=q2[i];
    divide(head,head+l1-1,l,mid);
    divide(tail-l2+1,tail,mid+1,r);
}

int prev(int x,int c)
{
    p=s[c].lower_bound(x);
    if (p!=s[c].begin()) return *(--p);
    else return 0;
}
int succ(int x,int c)
{
    p=s[c].upper_bound(x);
    if (p!=s[c].end()) return *p;
    else return 0;
}

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        s[a[i]].insert(i);
        int l=prev(i,a[i]);
        q[++num].tp=1;
        q[num].x=i; q[num].y=l;
    }
    char sign;
    int x,y;
    for (int i=1;i<=m;i++)
    {
        scanf("\n%c%d%d",&sign,&x,&y);
        if (sign=='Q') 
        {
            q[++num].tp=3;
            q[num].x=x; q[num].y=y;
            q[num].s=++cnt;
        }
        else
        {
            int l1=prev(x,a[x]),l2=prev(x,y);
            int r1=succ(x,a[x]),r2=succ(x,y);
            if (r1)
            {
                q[++num].tp=2; q[num].x=r1; q[num].y=x;
                q[++num].tp=1; q[num].x=r1; q[num].y=l1;
            }
            q[++num].tp=2; q[num].x=x; q[num].y=l1;
            q[++num].tp=1; q[num].x=x; q[num].y=l2;
            if (r2)
            {
                q[++num].tp=2; q[num].x=r2; q[num].y=l2;
                q[++num].tp=1; q[num].x=r2; q[num].y=x;
            }
            s[a[x]].erase(x);
            a[x]=y;
            s[a[x]].insert(x);
        }
    }
    divide(1,num,0,high);
    for (int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
    return 0;
}