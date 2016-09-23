//三维偏序
struct point{
    int x,y,z,s;
}a[maxn],q1[maxn],q2[maxn];
int f[maxn];
int n,m;
struct bit
{
    int b[maxn];
    void clear(int x){
        for (int i=x;i;i-=(i&-i)) b[i]=0;
    }
    void add(int x,int z){
        for (int i=x;i;i-=(i&-i)) b[i]=max(b[i],z);
    }
    int ask(int x){
        int tmp=0;
        for (int i=x;i<=n;i+=(i&-i)) tmp=max(b[i],tmp);
        return tmp;
    }
}s;

bool cmp1(point a,point b)
{    return a.x>b.x;}

bool cmp2(point a,point b)
{    return a.y>b.y;}

void solve(int l,int r){
    if (l==r) return ;
    int mid=(l+r)>>1;
    solve(l,mid);
    int t1=0,t2=0;
    for (int i=l;i<=mid;i++) q1[++t1]=a[i];
    for (int i=mid+1;i<=r;i++) q2[++t2]=a[i];
    sort(q1+1,q1+t1+1,cmp2);
    sort(q2+1,q2+t2+1,cmp2);
    int i=1;
    for (int j=1;j<=t2;j++){
        for (;q1[i].y>q2[j].y&&i<=t1;i++)
            s.add(q1[i].z,f[q1[i].s]);
        f[q2[j].s]=max(f[q2[j].s],s.ask(q2[j].z)+1);
    }
    for (int i=1;i<=t1;i++)
        s.clear(q1[i].z);
    solve(mid+1,r);
}

int main()
{
    //freopen("3sort.in","r",stdin);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z),a[i].s=i;
    sort(a+1,a+n+1,cmp1);
    for (int i=1;i<=n;i++) f[i]=1;
    solve(1,n);
    int ans=0;
    for (int i=1;i<=n;i++) ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}