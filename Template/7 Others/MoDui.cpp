//莫队算法
#define inf 2147483647
struct query
{
    int l,r,s,w;
}a[maxn];
int c[maxn];
long long col[maxn],size[maxn],ans[maxn];
int n,m,cnt,len;

long long gcd(long long x,long long  y)
{
    return (!x)?y:gcd(y%x,x);
}

bool cmp(query a,query b)
{
    return (a.w==b.w)?a.r<b.r:a.w<b.w;
}

int main()
{
    //freopen("hose.in","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&c[i]);
    len=(int)sqrt(m);
    cnt=(len*len==m)?len:len+1;
    for (int i=1;i<=m;i++) 
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        if (a[i].l>a[i].r) swap(a[i].l,a[i].r);
        size[i]=a[i].r-a[i].l+1;
        a[i].w=a[i].l/len+1;
        a[i].s=i;
    }
    sort(a+1,a+m+1,cmp);
    int i=1;
    while (i<=m)
    {
        int now=a[i].w;
        memset(col,0,sizeof(col));
        for (int j=a[i].l;j<=a[i].r;j++) ans[a[i].s]+=2*(col[c[j]]++);
        i++;
        for (;a[i].w==now;i++)
        {
            ans[a[i].s]=ans[a[i-1].s];
            for (int j=a[i-1].r+1;j<=a[i].r;j++)
                ans[a[i].s]+=2*(col[c[j]]++);
            if (a[i-1].l<a[i].l)
                for (int j=a[i-1].l;j<a[i].l;j++) 
                    ans[a[i].s]-=2*(--col[c[j]]);
            else
                for (int j=a[i].l;j<a[i-1].l;j++)
                    ans[a[i].s]+=2*(col[c[j]]++);
        }
    }
    long long all,num;
    for (int i=1;i<=m;i++)
    {
        if (size[i]==1) all=1; else all=size[i]*(size[i]-1);
        num=gcd(ans[i],all);
        printf("%lld/%lld\n",ans[i]/num,all/num);
    }
    return 0;
}    
