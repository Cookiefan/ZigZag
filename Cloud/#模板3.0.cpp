//=======数学=======
//高精度
struct high
{
	int e[100];
	void clean()
	{
		memset(e,0,sizeof(e));
	}
}a;

high operator +(high a,high b)
{
	high c; c.clean();
	c.e[0]=max(a.e[0],b.e[0]);
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i]+=a.e[i]+b.e[i];
		c.e[i+1]+=c.e[i]/p;
		c.e[i]=c.e[i]%p;
	}
	if (c.e[c.e[0]+1]) c.e[0]++;
	return c;
}

high operator -(high a, high b)
{
	high c; c.clean();
	int add=0;
	c.e[0]=max(a.e[0],b.e[0]);
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i]=a.e[i]-add-b.e[i];
		if (c.e[i]<0) c.e[i]+=p, add=1;
		else add=0;
	}
	while (c.e[c.e[0]]==0) c.e[0]--;
	return c;
}

high operator *(high a,high b)
{
	high c; c.clean();
	c.e[0]=a.e[0]+b.e[0]-1;
	for (int i=1;i<=a.e[0];i++)
		for (int j=1;j<=b.e[0];j++)
			c.e[i+j-1]+=a.e[i]*b.e[j];
	for (int i=1;i<=c.e[0];i++)
	{
		c.e[i+1]+=c.e[i]/p;
		c.e[i]=c.e[i]%p;
	}
	if (c.e[c.e[0]+1]) c.e[0]++;;
	return c;
}

high operator /(high a,int b)
{
	int down=0;
	high c; c.clean();
	c.e[0]=a.e[0];
	for (int i=a.e[0];i;i--)
	{
		c.e[i]=(a.e[i]+down*p)/b;
		down=(a.e[i]+down*p)-c.e[i]*b;
	}
	while ((c.e[c.e[0]]==0)&&(c.e[0]>0)) c.e[0]--;
	return c;
}

int operator %(high a,int b)
{
	int mod;
	for (int i=a.e[0];i;i--)
		mod=((mod*p%b)+a.e[i])%b;
	return mod;
}

high max(high a,high b)
{
	if (a.e[0]>b.e[0]) return a;
	if (a.e[0]<b.e[0]) return b;
	for (int i=a.e[0];i;i--)
	{
		if (a.e[i]>b.e[i]) return a;
		if (a.e[i]<b.e[i]) return b;
	}
	return a;
}

void read(high &a)
{
	char ch=getchar(); high x; x.clean();
	for (;ch<'0'||ch>'9';ch=getchar());
	for (;ch>='0'&&ch<='9';ch=getchar()) x.e[++x.e[0]]=ch-'0';
	for (int i=1;i<=x.e[0];i++) a.e[x.e[0]-i+1]=x.e[i];
	a.e[0]=x.e[0];
}

void write(high a)
{
	printf("%d",a.e[a.e[0]]);
	for (int i=a.e[0]-1;i>0;i--) printf("%d",a.e[i]);
	printf("\n");
}

//欧拉筛素数+欧拉函数
void get_prime(int n)
{
	memset(np,0,sizeof(np));
	phi[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!np[i])
		{
			prime.push_back(i);
			phi[i]=i-1;
		}
		for (int j=0;j<prime.size()&&prime[j]*i<=n;j++)
		{
			np[prime[j]*i]=1;
			if (i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

//莫比乌斯反演
void get_prime(int n)
{
    memset(np,0,sizeof(np));
    tot=0;
    mu[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!np[i])
        {
            prime[++tot]=i;
            mu[i]=-1;
        }
        for (int j=1;j<=tot && i*prime[j]<=n;j++)
        {
            np[i*prime[j]]=1;
            if (i%prime[j]) mu[i*prime[j]]=-mu[i];
            else
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
}

//求与序列中第j个数互质数的个数
int main()
{
	for (int i=1;i<=100000;i++)
        for (int j=i;j<=100000;j+=i)
            sum[i]+=v[j];
	for (int i=1;i<=100000;i++)
	{
	    for (int j=i;j<=100000;j+=i) f[j]+=sum[i]*mu[i];
	    if (i==1) f[i]--;
	}
}


//欧拉函数
int phi(long long x)
{
	long long cnt=x;
	for (long long i=2;i*i<=x;i++)
		if (x%i==0)
		{
			cnt=cnt/i*(i-1);
			while (x%i==0) x=x/i;
		}
	if (x>1) cnt=cnt/x*(x-1);
	return cnt;
}

//扩展欧几里得
LL ex_gcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x=1, y=0;
        return a;
    }
    else
    {
        LL d=ex_gcd(b, a % b, y, x);
        y-=a/b*x;
        return d;
    }
}

//求乘法逆元
LL inv(LL a, LL p)
{
	LL gcd, x, y;
	gcd=ex_gcd(a, p, x, y);
	if (gcd==1) return (x+p)%p;
	else return -1;
}

//递归求逆元
LL rev(LL x)
{
	if (x==1) return 1;
	else return (oo-oo/x)*rev(oo%x)%oo;
}

//中国剩余定理(互质)
LL crt(int n, LL* a, LL* p)
{
    LL pp=1, tmp=0;
    for(int i=0;i<n;i++) pp=pp*p[i];
    for(int i=0;i<n;i++)
    {
        LL m=pp/p[i], x, y;
        ex_gcd(m,p[i],x,y);
        x=(x%p[i]+p[i])%p[i];
        tmp=(tmp+(a[i]*m%pp*x)%pp)%pp;//注意overflow
    }
    return tmp;
}

//矩阵乘法&快速幂
struct matrix
{
	llg e[maxn][maxn];
	matrix()
	{
		memset(e,0,sizeof(e));
	}
	matrix(int x)
	{
		memset(e,0,sizeof(e));
		for (int i=0;i<4;i++) e[i][i]=x;
	}
	void clear()
	{
		memset(e,0,sizeof(e));
	}
	friend matrix operator *(matrix a, matrix b)
	{
		matrix c;
		for (int k=0;k<4;k++)
			for (int i=0;i<4;i++)
				for (int j=0;j<4;j++)
					(c.e[i][j]+=a.e[i][k]*b.e[k][j]%q)%=q;
		return c;
	}
	friend matrix operator ^(matrix e, llg k)
	{
		matrix tmp=matrix(1);
		while (k)
		{
			if (k&1) tmp=tmp*e;
			k=k>>1;
			e=e*e;
		}
		return tmp;
	}
};

//慢速乘
llg mul(llg a,llg b,llg p)
{
	a%=p,b%=p;
	llg tmp=0;
	while (b)
	{
		if (b&1) tmp=(tmp+a)%p;
		a=(a+a)%p;
		b/=2;
	}
	return tmp;
}

//快速幂
LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp=(tmp*a)%p;
		a=a*a%p;
		b=b/2;
	}
	return tmp;
}

//Lucas定理(求组合数取模,注意p<=10^5)
LL com(LL n,LL m,LL p)
{
	if (m>n) return 0;
	LL ans=1;
	for (int i=1;i<=m;i++)
	{
		ans=ans*(n-i+1)%p;
		ans=ans*exp(i,p-2,p)%p;
	}
	return ans;
}

LL lucas(LL n,LL m,LL p)
{
	if (m==0) return 1;
	return (com(n%p,m%p,p)*lucas(n/p,m/p,p))%p;
}

LL get_ans(LL n, LL m)
{
	return lucas(n+m,n,oo);
}




//miller_rabin+pollard_rho分解质因数
const int S=20;//随机算法判定次数，S越大，判错概率越小
//计算 (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
//  a,b,c <2^63
long long mult_mod(long long a,long long b,long long c)
{
    a%=c;
    b%=c;
    long long ret=0;
    while(b)
    {
        if(b&1){ret+=a;ret%=c;}
        a<<=1;
        if(a>=c)a%=c;
        b>>=1;
    }
    return ret;
}

//计算  x^n %c
long long pow_mod(long long x,long long n,long long mod)//x^n%c
{
    if(n==1)return x%mod;
    x%=mod;
    long long tmp=x;
    long long ret=1;
    while(n)
    {
        if(n&1) ret=mult_mod(ret,tmp,mod);
        tmp=mult_mod(tmp,tmp,mod);
        n>>=1;
    }
    return ret;
}

//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(long long a,long long n,long long x,long long t)
{
    long long ret=pow_mod(a,x,n);
    long long last=ret;
    for(int i=1;i<=t;i++)
    {
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;//合数
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}

// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;

bool Miller_Rabin(long long n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//偶数
    long long x=n-1;
    long long t=0;
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
    {
        long long a=rand()%(n-1)+1;//rand()需要stdlib.h头文件
        if(check(a,n,x,t))
            return false;//合数
    }
    return true;
}

//pollard_rho 算法进行质因数分解
long long factor[100];//质因数分解结果（刚返回时是无序的）
int tol;//质因数的个数。数组小标从0开始

long long gcd(long long a,long long b)
{
    return (b==1?a:gcd(b, a%b));
}

long long Pollard_rho(long long x,long long c)
{
    long long i=1,k=2;
    long long x0=rand()%x;
    long long y=x0;
    while(1)
    {
        i++;
        x0=(mult_mod(x0,x0,x)+c)%x;
        long long d=gcd(y-x0,x);
        if(d!=1&&d!=x) return d;
        if(y==x0) return x;
        if(i==k){y=x0;k+=k;}
    }
}
//对n进行素因子分解
void findfac(long long n)
{
    if(Miller_Rabin(n))//素数
    {
        factor[tol++]=n;
        return;
    }
    long long p=n;
    while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
    findfac(p);
    findfac(n/p);
}

int main()
{
    //srand(time(NULL));//需要time.h头文件//POJ上G++不能加这句话
    long long n;
    while(scanf("%I64d",&n)!=EOF)
    {
        tol=0;
        findfac(n);
        for(int i=0;i<tol;i++)printf("%I64d ",factor[i]);
        printf("\n");
        if(Miller_Rabin(n))printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

//=======动态规划=======

//数位动归
int get_ans(int x)
{
	if (!x) return 1;
	int len=0,tmp=0;
	while (x)
	{
		b[++len]=x%10;
		x=x/10;
	}
	b[1]++;
	b[len+1]=0;
	b[len+2]=0;
	for (int i=len;i>=1;i--)//固定第i+1位之前的位
	{
		if (b[i+1]==4) break;
		if (b[i+2]==6&&b[i+1]==2) break;
		for (int j=0;j<b[i];j++)//枚举第i位
		{
			if ((b[i+1]==6&&j==2)||(j==4)) continue ;
			tmp+=f[i-1][0]+f[i-1][1]*(j!=6);
		}
	}
	return tmp;
}

//四边形不等式

for (int len=2;len<=n;len++)
{
	for (int i=1;i<=n-len+1;i++)
	{
		int j=i+len-1;
		f[i][j]=inf;
		for (int k=K[i][j-1];k<=min(j-1,K[i+1][j]);k++)
		{
			if (f[i][j]>f[i][k]+f[k+1][j]+x[k+1]-x[i]+y[k]-y[j])
			{
				f[i][j]=f[i][k]+f[k+1][j]+x[k+1]-x[i]+y[k]-y[j];
				K[i][j]=k;
			}
		}
	}
}

//=======字符串=======

//KMP
int kmp(char *t)
{
	int n=strlen(t);
	memset(nxt,-1,sizeof(nxt));
	int j=-1;
	for (int i=1;i<n;i++)
	{
		while (j!=-1&&t[i]!=t[j+1]) j=nxt[j];
		if (t[i]==t[j+1]) j++;
		nxt[i]=j;
	}
	return n-1-nxt[n-1];//n-next[n-1]是最小循环节
}
void match(char *s, char *t)
{
	int ls=strlen(s), lt=strlen(t);
	int j=-1;
	for (int i=0;i<ls;i++)
	{
		while (j!=-1 && s[i]!=t[j+1]) j=nxt[j];
		if (s[i]==t[j+1]) j++;
	}
}

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

//=======数据结构=======

//set启发式合并
int merge(int x,int y)
{
	int tmp=inf;
	SIT prev,succ;
	if (s[x].size()<s[y].size()) swap(s[x],s[y]);
	for (SIT i=s[y].begin();i!=s[y].end();i++)
	{
		prev=succ=s[x].lower_bound(*i);
		if (prev!=s[x].begin()) prev--;
		if (prev!=s[x].end())	tmp=min(tmp,abs(*prev-*i));
		if (succ!=s[x].end())   tmp=min(tmp,abs(*succ-*i));
		s[x].insert(*i);
	}
	s[y].clear();
	return tmp;
}

//BIT改段求段
struct bit
{
	int b[maxn];
	int num;
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) b[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i;i-=(i&-i)) tmp+=b[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(b,0,sizeof(b));
	}
}s,t;

void ins(int x,int y,int z)
{
	s.add(x,z); s.add(y+1,-z);
	t.add(x,z*x); t.add(y+1,-z*(y+1));
}

int query(int x,int y)
{
	int tmp=s.ask(y)*(y+1)-s.ask(x-1)*x-(t.ask(y)-t.ask(x-1));
	return tmp;
}

//BIT求最值
struct mx_bit
{
	int mx[maxn],key[maxn];
	int num;
	void cov(int x,int z)
	{
		key[x]=z;
		for (int i=x;i<=num;i+=(i&-i)) mx[i]=max(mx[i],z);
	}
	int ask(int l,int r)
	{
		int tmp=-inf;
		while (l<=r)
		{
			tmp=max(tmp,key[r]);
			for (r-=1;r-(r&-r)>=l;r-=(r&-r)) tmp=max(tmp,mx[r]);
		}
		return tmp;
	}
	void init(int x)
	{
		num=x;
		memset(mx,0,sizeof(mx));
		memset(key,0,sizeof(key));
	}
}tree;

//线段树最大连续1
struct segtree
{
	int mx[maxn*8], lmx[maxn*8], rmx[maxn*8], size[maxn*8];
	void update(int x)
	{
		mx[x]=max(max(mx[x*2],mx[x*2+1]),rmx[x*2]+lmx[x*2+1]);
		if (lmx[x*2]==size[x*2]) lmx[x]=size[x*2]+lmx[x*2+1];
		else lmx[x]=lmx[x*2];
		if (rmx[x*2+1]==size[x*2+1]) rmx[x]=size[x*2+1]+rmx[x*2];
		else rmx[x]=rmx[x*2+1];
	}
	void build(int x,int l,int r)
	{
		if (l==r)
		{
			size[x]=1;
			return ;
		}
		int mid=(l+r)>>1;
		build(x*2,l,mid);
		build(x*2+1,mid+1,r);
		size[x]=size[x*2]+size[x*2+1];
	}
	void add(int x, int l, int r, int pos, int z)
	{
		if (l==r)
		{
			mx[x]=lmx[x]=rmx[x]=z;
			return ;
		}
		int mid=(l+r)>>1;
		if (pos<=mid) add(x*2, l, mid, pos, z);
		else add(x*2+1, mid+1, r, pos, z);
		update(x);
	}
	int ask(int x, int l, int r, int ll, int rr, int &res)
	{
		if (ll<=l && r<=rr)
		{
			int tmp=max(res+lmx[x], mx[x]);
			if (rmx[x]==size[x]) res+=size[x];
			else res=rmx[x];
			return tmp;
		}
		int mid=(l+r)>>1, tmp=0;
		if (ll<=mid) tmp=max(tmp,ask(x*2, l, mid, ll, rr, res));
		if (rr>mid) tmp=max(tmp,ask(x*2+1, mid+1, r, ll, rr, res));
		return tmp;
	}
	void init()
	{
		memset(mx,0,sizeof(mx));
		memset(lmx,0,sizeof(lmx));
		memset(rmx,0,sizeof(rmx));
	}
}tree;

//主席树
struct node
{
	node *lc,*rc;
	int s;
	node () {s=0;}
}*rot[maxn],*sum[maxn],*p;
vector <node*> st[4];
struct et
{
	int s,t,next;
}e[maxn*2];
int ll[maxn],rr[maxn],fir[maxn],key[maxn];
int w[maxn*2],dep[maxn],fa[maxn][20];
int x[maxn],y[maxn],z[maxn];
int n,m,tot,low,cnt,num;
int v[5];

node *build(int l,int r)
{
	node *now=new node();
	if (l==r) return now;
	int mid=(l+r)>>1;
	now->lc=build(l,mid);
	now->rc=build(mid+1,r);
	return now;
}

node *change(int l,int r,int x,int z)
{
	node *now=new node();
	now->lc=p->lc; now->rc=p->rc;
	now->s=p->s+z;
	if (l==r) return now;
	int mid=(l+r)>>1;
	if (x<=mid) p=p->lc,now->lc=change(l,mid,x,z);
	else p=p->rc,now->rc=change(mid+1,r,x,z);
	return now;
}
	
void adj(int x,int y,int z)
{
	if (x==0) return ;
	for (int i=x;i<=n;i+=(i&-i)) p=rot[i],rot[i]=change(0,num,y,z);
}       

void fill(int k)
{
	st[k].clear();
	st[k].push_back(sum[v[k]]);
	for (int i=ll[v[k]];i>0;i-=(i&-i)) st[k].push_back(rot[i]);
}

int getsum(int k)
{
	int ans=0, n=st[k].size();
	for (int i=0;i<n;i++) ans+=st[k][i]->s;
	return ans;
}

int getsize(int k)
{
	int ans=0, n=st[k].size();
	for (int i=0;i<n;i++) ans+=st[k][i]->rc->s;
	return ans;
}

void goleft(int k)
{
	int n=st[k].size();
	for (int i=0;i<n;i++) st[k][i]=st[k][i]->lc;
}

void goright(int k)
{
	int n=st[k].size();
	for (int i=0;i<n;i++) st[k][i]=st[k][i]->rc;
}

int query(int l,int r,int k)
{
	if (k>getsum(1)+getsum(2)-getsum(3)-getsum(4)) return 0;
	if (l==r) return l;
	int tmp=getsize(1)+getsize(2)-getsize(3)-getsize(4);
	//cout<<l<<' '<<r<<"tmp:"<<tmp<<endl;
	int mid=(l+r)>>1;
	if (k<=tmp)
	{
		//cout<<"right\n";
		goright(1),goright(2),goright(3),goright(4);
		return query(mid+1,r,k);
	}
	else
	{
		//cout<<"left\n";
		goleft(1),goleft(2),goleft(3),goleft(4);
		return query(l,mid,k-tmp);
	}
}

int lca(int x,int y)
{
	if (dep[x]>dep[y]) swap(x,y);
	for (int i=low;i>=0;i--) 
		if (dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if (x==y) return x;
	for (int i=low;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void write(node *now,int l,int r)
{
	if (l==r)
	{
		cout<<now->s;
		return ;
	}
	int mid=(l+r)>>1;
	write(now->lc,l,mid);
	write(now->rc,mid+1,r);
}

void dfs(int now)
{
	ll[now]=rr[now]=++cnt;
	p=sum[fa[now][0]];
	sum[now]=change(0,num,key[now],1);

	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (fa[now][0]!=k)
		{
			fa[k][0]=now; dep[k]=dep[now]+1;
			for (int i=1;i<=low;i++) fa[k][i]=fa[fa[k][i-1]][i-1];
			dfs(k);
			rr[now]=rr[k];
		}       
	} 
}

void add(int x,int y)
{       
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
	e[++tot].s=y; e[tot].t=x; e[tot].next=fir[y]; fir[y]=tot; 
}
	
int main()
{
	//freopen("network10.in","r",stdin);
	//freopen("network.out","w",stdout);
	scanf("%d%d",&n,&m);
	low=log(n)/log(2.0);
	for (int i=1;i<=n;i++) scanf("%d",&key[i]),w[++num]=key[i];
	int st,ed;
	for (int i=1;i<n;i++) scanf("%d%d",&st,&ed),add(st,ed);
	num=n;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&z[i],&x[i],&y[i]);
		if (!z[i]) w[++num]=y[i];
	}
	sort(w+1,w+num+1);
	num=unique(w+1,w+num+1)-w;
	for (int i=1;i<=n;i++) key[i]=lower_bound(w+1, w+num+1, key[i])-w;
	for (int i=1;i<=m;i++) if (!z[i]) y[i]=lower_bound(w+1, w+num+1, y[i])-w;

	sum[0]=rot[0]=build(0,num);
	for (int i=1;i<=n;i++) rot[i]=rot[0];
	int root=rand()%n+1; dep[root]=1;
	dfs(root);

	for (int i=1;i<=m;i++)
	{
		if (z[i])
		{
			int tmp;
			v[1]=x[i],v[2]=y[i],v[3]=tmp=lca(x[i],y[i]),v[4]=fa[tmp][0];
			fill(1); fill(2); fill(3); fill(4);
			int ans=query(0,num,z[i]);
			if (ans)
				printf("%d\n",w[ans]);
			else 
				printf("invalid request!\n");
		}
		else
		{
			adj(ll[x[i]],key[x[i]],-1),adj(rr[x[i]]+1,key[x[i]],1);
			key[x[i]]=y[i];
			adj(ll[x[i]],key[x[i]],1),adj(rr[x[i]]+1,key[x[i]],-1);
		}
	}

	return 0;
}

//Splay区间维护
//支持区间求和，最大连续子段，区间反转，区间覆盖操作
int c[maxn][2],fa[maxn];
int a[maxn],key[maxn],sum[maxn],la[maxn],ra[maxn],ma[maxn],cov[maxn],size[maxn];
int q[maxn];
bool rev[maxn];
int n,m,tot,num,rot,st,ed,tail;

void update(int x)
{
    if (!x) return;
    la[x]=max(la[c[x][0]],sum[c[x][0]]+key[x]+max(0,la[c[x][1]]));
    ra[x]=max(ra[c[x][1]],sum[c[x][1]]+key[x]+max(0,ra[c[x][0]]));
    ma[x]=max(max(ma[c[x][0]],ma[c[x][1]]),key[x]+max(0,ra[c[x][0]])+max(0,la[c[x][1]]));
    sum[x]=sum[c[x][0]]+sum[c[x][1]]+key[x];
    size[x]=size[c[x][0]]+size[c[x][1]]+1;
}

void reverse(int x)
{
    if (!x) return;
    swap(c[x][0],c[x][1]);
    swap(la[x],ra[x]);
    rev[x]^=1;
}

void recover(int x,int z)
{
    if (!x) return ;
    key[x]=cov[x]=z;
    sum[x]=size[x]*z;
    la[x]=ra[x]=ma[x]=max(z,sum[x]);
}

void down(int x)
{
    if (!x) return;
    if (rev[x])
    {
        reverse(c[x][0]);
        reverse(c[x][1]);
        rev[x]=0;
    }
    if (cov[x]!=-inf)
    {
        recover(c[x][0],cov[x]);
        recover(c[x][1],cov[x]);
        cov[x]=-inf;
    }
}

void relax(int x,int rot)
{
    if (x!=rot) relax(fa[x],rot);
    down(x);
}

void rotate(int x,int &rot)
{
    int y=fa[x],z=fa[y];
    int p=(c[y][1]==x),q=p^1;
    if (y==rot) rot=x; 
    c[z][c[z][1]==y]=x;
    fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
    c[y][p]=c[x][q]; c[x][q]=y;
    update(y);
}

void splay(int x,int &rot)
{
    relax(x,rot);
    while (x!=rot)
    {
        int y=fa[x], z=fa[y];
        if (y!=rot)
        {
            if ((c[y][0]==x)xor(c[z][0]==y)) rotate(x,rot);
            else rotate(y,rot);
        }
        rotate(x,rot);
    }
    update(x);
}

int pick()
{
    if (tail) return q[tail--];
    else return ++num;
}

int setup(int x)
{
    int t=pick();
    key[t]=a[x];
    cov[t]=-inf;
    rev[t]=0;
    la[t]=ra[t]=ma[t]=-inf;
    return t;
}

int build(int l,int r)
{
    int mid=(l+r)>>1,left=0,right=0;
    if (l<mid)      left=build(l,mid-1);
    int t=setup(mid);
    if (r>mid)      right=build(mid+1,r);
    if (left)       c[t][0]=left,fa[left]=t;
    if (right)c[t][1]=right,fa[right]=t;
    update(t);
    return t;
}

int find(int t,int k)
{
    down(t);
    if (k==size[c[t][0]]+1) return t;
    if (k<size[c[t][0]]+1) return find(c[t][0],k);
    if (k>size[c[t][0]]+1) return find(c[t][1],k-size[c[t][0]]-1);
}

void del(int &x)
{
    if (!x) return;
    q[++tail]=x;
    fa[x]=0;
    del(c[x][0]);
    del(c[x][1]);
    la[x]=ra[x]=ma[x]=-inf;
    x=0;
}

int main()
{
    //freopen("build.in","r",stdin);
    //freopen("build.out","w",stdout);
    scanf("%d %d",&n,&m);
    for (int i=2;i<=n+1;i++)
            scanf("%d",&a[i]);      
    a[st=1]=0; a[ed=n+2]=0;
    ra[0]=la[0]=ma[0]=-inf;
    rot=build(1,n+2);
    char sign[20];
    int x,y,l,r,z,ans;
    for (int i=1;i<=m;i++)
    {
        scanf(" %s",sign);
        if (sign[0]=='I')
        {
            scanf("%d %d",&x,&y);
            l=find(rot,x+1); r=find(rot,x+2);
            splay(r,rot); splay(l,c[rot][0]);
            for (int j=1;j<=y;j++) 
                scanf("%d",&a[j]);
            int tmp=build(1,y);
            fa[tmp]=l; c[l][1]=tmp;                 
            update(l); update(r);
        }
        if (sign[0]=='D')
        {
            scanf("%d %d",&x,&y);
            l=find(rot,x);  r=find(rot,x+y+1);
            splay(r,rot); splay(l,c[rot][0]);
            del(c[l][1]);
            update(l); update(r);
        }                       
        if (sign[0]=='M'&&sign[2]=='K')
        {
            scanf("%d %d %d",&x,&y,&z);
            l=find(rot,x); r=find(rot,x+y+1);
            splay(r,rot); splay(l,c[rot][0]);
            recover(c[l][1],z);
        }
        if (sign[0]=='R')
        {
            scanf("%d %d",&x,&y);
            l=find(rot,x); r=find(rot,x+y+1);
            splay(r,rot); splay(l,c[rot][0]);
            reverse(c[l][1]);
        }
        if (sign[0]=='G')
        {
            scanf("%d %d",&x,&y);
            l=find(rot,x); r=find(rot,x+y+1);
            splay(r,rot); splay(l,c[rot][0]);
            ans=sum[c[l][1]];
            printf("%d\n",ans);
        }
        if (sign[0]=='M'&&sign[2]=='X')
        {
            splay(ed,rot); splay(st,c[rot][0]);
            ans=ma[c[st][1]];
            printf("%d\n",ans);
        }
    }
    return 0;
}

//Link-Cut-Tree
//支持4种操作
//1.连接x-y将两棵树合并
//2.将x变成根，并切除y与其父亲的连边
//3.将x-y路径上的节点权值+z
//4.询问x-y路径上的最大值
int n,m,tot,q;
int fir[maxn],fa[maxn],c[maxn][2];
int mxv[maxn],key[maxn],rev[maxn],add[maxn];
struct edge
{
	int s,t,val,next;
}e[maxm];
void add_edge(int x,int y)
{
	e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x];fir[x]=tot;
}
void dfs(int x)
{
	for (int j=fir[x];j;j=e[j].next)
	{
		int k=e[j].t;
		if (k!=fa[x])
		{
			fa[k]=x;
			dfs(k);
		}
	}
}

void update(int x)
{
	if (!x) return ;
	mxv[x]=max(max(mxv[c[x][0]],mxv[c[x][1]]),key[x]);
}
void reverse(int x)
{
	if (!x) return ;
	swap(c[x][0],c[x][1]);
	rev[x]^=1;
}
void add_key(int x,int z)
{
	if (!x) return ;
	key[x]+=z;
	mxv[x]+=z;
	add[x]+=z;
}

void down(int x)
{
	if (rev[x])
	{
		reverse(c[x][0]);
		reverse(c[x][1]);
		rev[x]=0;
	}
	if (add[x])
	{
		add_key(c[x][0],add[x]);
		add_key(c[x][1],add[x]);
		add[x]=0;
	}
}

bool is_root(int x)
{
	return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}

void relax(int x)
{
	if (!is_root(x)) relax(fa[x]);
	down(x);
}

void zigzag(int x)
{
	int y=fa[x],z=fa[y];
	int p=(c[y][1]==x), q=p^1;
	if (!is_root(y))
	{
		if (c[z][0]==y) c[z][0]=x; else c[z][1]=x;
	}
	fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
	c[y][p]=c[x][q]; c[x][q]=y;
	update(y);
}

void splay(int x)
{
	relax(x);
	while (!is_root(x))
	{
		int y=fa[x],z=fa[y];
		if (!is_root(y))
		{
			if ((c[y][0]==x)^(c[z][0]==y)) zigzag(x); else zigzag(y);
		}
		zigzag(x);
	}
	update(x);
}

int access(int x)
{
	int y=0;
	for (;x;x=fa[x])
	{
		splay(x);
		c[x][1]=y;
		update(x);
		y=x;
	}
	return y;
}

void make_root(int x)
{
	access(x);
	splay(x);
	reverse(x);
}

int root(int x)
{
	while (fa[x]) x=fa[x];
	return x;
}

void link(int x, int y)
{
	make_root(x);
	fa[x]=y;
}

void cut(int x, int y)
{
	make_root(x);
	splay(y);
	if (c[y][0])
	{
		fa[c[y][0]]=fa[y];	
		c[y][0]=0;
	}
	fa[y]=0;
}

void change(int x, int y, int z)
{
	access(x);
	int lca=access(y);
	splay(x);
	key[lca]+=z;
	add_key(c[lca][1],z);
	if (x!=lca) add_key(x,z);
}

int ask(int x, int y)
{
	access(x); 
	int lca=access(y);
	splay(x);
	if (x==lca) return max(mxv[c[lca][1]],key[lca]);
	else return max(max(mxv[c[lca][1]],key[lca]),mxv[x]);
}

void init()
{
	tot=1;
	memset(fir,0,sizeof(fir));
	memset(key,0,sizeof(key));
	memset(mxv,0,sizeof(mxv));
	memset(rev,0,sizeof(rev));
	memset(add,0,sizeof(add));
	memset(c,0,sizeof(c));
	memset(fa,0,sizeof(fa));
}

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		int x,y,z,s;
		init();
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			add_edge(x,y);
			add_edge(y,x);
		}
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			key[i]=x;
			mxv[i]=x;
		}
		dfs(1);
		scanf("%d",&m);
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&s);
			switch(s)
			{
				case 1:
					scanf("%d%d",&x,&y);
					if (root(x)!=root(y)) link(x,y);
					else printf("-1\n");
				break;

				case 2:
					scanf("%d%d",&x,&y);
					if (root(x)==root(y) && x!=y) cut(x,y);
					else printf("-1\n");
				break;

				case 3:
					scanf("%d%d%d",&z,&x,&y);
					if (root(x)==root(y)) change(x,y,z);
					else printf("-1\n");
				break;

				case 4:
					scanf("%d%d",&x,&y);
					if (root(x)==root(y)) printf("%d\n",ask(x,y));
					else printf("-1\n");
				break;
			}
		}
		printf("\n");
	}
	return 0;
}

//分治求逆序对
void solve(int l, int r)
{
	if (l==r) return ;
	int mid=(l+r)>>1;
	solve(l, mid);
	solve(mid+1, r);
	int i=l, j=mid+1, k=0;
	while (i<=mid || j<=r)
	{
		if (j>r || i<=mid && q[i]<=q[j]) nq[k++]=q[i++], sum+=(j-mid-1);
		else
		if (i>mid || j<=r && q[i]>q[j]) nq[k++]=q[j++];
	}
	for (int i=0;i<k;i++) q[l+i]=nq[i];
}

//CDQ分治(带修改区间k大)
int n,m,tot,cnt;
int a[maxn], ans[maxm];

struct query
{
	int id,x,y,k,cur;
	query(){}
	query(int id,int x,int y,int k,int cur):
		id(id),x(x),y(y),k(k),cur(cur){}
}q[maxm],q1[maxm],q2[maxm];

struct bit
{
	int num;
	int s[maxn];
	void add(int x,int z)
	{
		for (int i=x;i<=num;i+=(i&-i)) s[i]+=z;
	}
	int ask(int x)
	{
		int tmp=0;
		for (int i=x;i>=1;i-=(i&-i)) tmp+=s[i];
		return tmp;
	}
	void init(int n)
	{
		num=n;
		memset(s,0,sizeof(s));
	}
}tree;

void solve(int st,int ed,int l,int r)
{
	if (st>ed) return ;
	if (l==r)
	{
		for (int i=st;i<=ed;i++) ans[q[i].id]=l;
		return ;
	}
	int mid=(l+r)>>1, n1=0, n2=0;;
	for (int i=st;i<=ed;i++)
	{
		if (q[i].id==0)
		{
			if (q[i].y<=mid)
			{
				tree.add(q[i].x, q[i].k);
				q1[n1++]=q[i];
			}
			else
				q2[n2++]=q[i];
		}
		else
		{
			int tmp=tree.ask(q[i].y)-tree.ask(q[i].x-1);
			if (q[i].cur+tmp>=q[i].k) 
				q1[n1++]=q[i];
			else 
			{
				q[i].cur+=tmp;
				q2[n2++]=q[i];
			}
		}
	}
	for (int i=st;i<=ed;i++)
		if (q[i].id==0 && q[i].y<=mid) tree.add(q[i].x, -q[i].k);
	for (int i=0;i<n1;i++) q[st+i]=q1[i];
	for (int i=0;i<n2;i++) q[st+n1+i]=q2[i];
	solve(st,st+n1-1,l,mid);
	solve(st+n1,ed,mid+1,r);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--)
	{
		scanf("%d%d",&n,&m);
		tot=cnt=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			q[tot++]=query(0,i,a[i],1,0);
		}
		int x,y,z;
		char sign;
		for (int i=1;i<=m;i++)
		{
			scanf(" %c",&sign);
			if (sign=='C')
			{
				scanf("%d%d",&x,&y);
				q[tot++]=query(0,x,a[x],-1,0);
				a[x]=y;
				q[tot++]=query(0,x,a[x],1,0);
			}
			else
			{	
				scanf("%d%d%d",&x,&y,&z);
				q[tot++]=query(++cnt,x,y,z,0);
			}
			
		}
		tree.init(n);
		solve(0,tot-1,0,inf);
		for (int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
	}
	return 0;
}

//=======图论=======

//倍增LCA
void set_father(int n)
{
	for (int k=1;k<=low;k++)
		for (int i=1;i<=n;i++)
			fa[i][k]=fa[fa[i][k-1]][k-1];
}

int get_father(int x,int y)
{
	if (dep[x]>dep[y]) swap(x,y);
	for (int i=low;i>=0;i--)
		if (dep[fa[y][i]]>=dep[x]) y=fa[y][i];
	if (x==y) return x;
	for (int i=low;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

//堆DJ
struct node
{
	int id,dis;
	node(){}
	node(int x,int y)
	{
		id=x; dis=y;
	}
	friend bool operator <(node a,node b)
	{ 
		return a.dis>b.dis;
	}
};

priority_queue<node> q;

void dij(int st)
{
	for (int i=1;i<=n;i++) dis[i]=inf;
	memset(vis,0,sizeof(vis));
	while (!q.empt y()) q.pop();
	q.push(node(st,0));
	dis[st]=0;
	while (!q.empty())
	{
		int i=q.top().id;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!vis[k]&&dis[i]+e[j].val<dis[k])
			{
				dis[k]=dis[i]+e[j].val;
				q.push(node(k,dis[k]));
			}
		}
	}
}

//floyd最小环
for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
		a[i][j]=d[i][j]=inf;
for (int i=1;i<=m;i++)
{
	scanf("%d%d%d",&x,&y,&z);
	if (z<a[x][y])
	{
		a[x][y]=a[y][x]=z;
		d[x][y]=d[y][x]=z;
	}
}
ans=inf;
for (int k=1;k<=n;k++)
{
	for (int i=1;i<k;i++)
		for (int j=i+1;j<k;j++)
			ans=min(ans,d[i][j]+a[j][k]+a[k][i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			d[i][j]=min(d[i][j],dis[i][k]+dis[k][j]);
}

//负环spfa
queue<int> q;

bool neg_loop(int st)
{
	while (!q.empty()) q.pop();
	for (int i=0;i<=n;i++) dis[i]=inf;
	memset(times,0,sizeof(times));
	memset(vis,0,sizeof(vis));
	q.push(st);
	vis[st]=1;
	times[st]=1;
	dis[st]=0;
	while (!q.empty())
	{
		int i=q.front();
		q.pop();
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (dis[k]>dis[i]+e[j].val)
			{
				dis[k]=dis[i]+e[j].val;
				if (!vis[k])
				{
					q.push(k);
					vis[k]=1;
					times[k]++;
					if (times[k]>=n) return 1;
				}
			}
		}
		vis[i]=0;
	}
	return 0;
}

//prim算法
void prim()
{
    int ans=0;
    for (int i=1;i<=n;i++) d[i]=e[0][i],v[i]=0;
    v[0]=1;
    for (int i=1;i<=n;i++)
    {
        int min=inf,k;
        for (int j=1;j<=n;j++)
            if (!v[j]&&d[j]<min)
            {
                min=d[j];
                k=j;
            }
        v[k]=1;
        ans+=min;
        for (int j=1;j<=n;j++)
        if (!v[j]&&e[k][j]<d[j])
			d[j]=e[k][j];
    }
    printf("%d\n",ans);
}

//堆优化prim

priority_queue<node> q;

int prim(int n)
{
    int ans=0;
    memset(vis,0,sizeof(vis));
    for (int i=0;i<=n;i++) dis[i]=inf;
    while (!q.empty())q.pop();
	q.push(node(0,0));
    dis[0]=0;
    while (!q.empty())
    {
    	int i=q.top().id;
    	q.pop();
    	if (vis[i]) continue;
    	vis[i]=1;
    	ans+=dis[i];
        for (int j=fir[i];j;j=e[j].next)
        {
        	int k=e[j].t;
        	if (!vis[k] && e[j].val<dis[k])
        	{
				dis[k]=e[j].val;
				q.push(node(k,dis[k]));
        	}
		}
    }
    return ans;
}


//tarjan强连通分量
void tarjan(int now)
{
    dfn[now]=low[now]=++tim;
	stack[++top]=now;
    v[now]=1;
	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k]) tarjan(k);
		if (v[k]<2) low[now]=min(low[now],low[k]);
	}
	if (dfn[now]==low[now])
	{
		num++;
		while (stack[top+1]!=now)
		{
			web[stack[top]]=num;
			v[stack[top--]]=2;
		}
    }
}
//tarjan割点
void tarjan(int now)
{
    dfn[now]=low[now]=++tim;
    v[now]=1;
    for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k])
		{
			tarjan(k);
			low[now]=min(low[now],low[k]);
			if (dfn[now]<=low[k]) v[now]++;
		}
		else
			low[now]=min(low[now],dfn[k]);
	}
	if ((dfn[now]==1&&v[now]>2)||(dfn[now]>1&&v[now]>1))
		cut[now]=1;
}
//tarjan割边
void tarjan(int i)
{
	vis[i]=1;
	dfn[i]=low[i]=++cnt;
	for (int j=fir[i];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!vis[k])
		{
			pre[k]=j^1;
			tarjan(k);
			low[i]=min(low[i],low[k]);
		}
		else if (j!=pre[i])
			low[i]=min(low[i],dfn[k]);
	}
	if (pre[i] && dfn[i]==low[i]) bridge[pre[i]]=bridge[pre[i]^1]=1;
}

//匈牙利算法(二分图匹配)
bool match(int i)
{
	for (int j=fir[i];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!vis[k])
		{
			vis[k]=1;
			if ((!mch[k])||(match(mch[k])))
			{
				mch[k]=i;
				return 1;
			}
		}
	}
	return 0;
}

int hungary()
{
	int tmp=0;
	memset(mch,0,sizeof(mch));
	for (int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if (match(i)) tmp++;
	}
	return tmp;
}

//最大流sap
int dfs(int now,int flow)
{
	if (now==ed) return flow;
	int sap=0;
	for (int j=last[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (e[j].val&&dis[now]==dis[k]+1)
		{
			last[now]=j;
			int tmp=dfs(k,min(e[j].val,flow-sap));
			e[j].val-=tmp;
			e[j^1].val+=tmp;
			sap+=tmp;
			if (sap==flow) return sap;
		}
	}
	if (dis[st]>=num) return sap;
	if (!(--gap[dis[now]])) dis[st]=num;
	++gap[++dis[now]];
	last[now]=fir[now];
	return sap;
}

//spfa费用流(max)
bool find()
{
	for (int i=st;i<=ed;i++) d[i]=-inf;
	int head=0,tail=1;
	q[1]=st,d[st]=0,inque[st]=1;
	while (head<tail)
	{
		int now=q[++head];
		for (int j=fir[now];j;j=e[j].next)
		{
			int k=e[j].t;
			if (e[j].val&&d[k]<d[now]+e[j].cost)
			{
				d[k]=d[now]+e[j].cost;
				pre[k]=j;
				if (!inque[k]) q[++tail]=k，inque[k]=1;
			}
		}
		inque[now]=0;
	}
	return (d[ed]>-inf) ;
}

void fare_flow()
{
	fare=flow=0;
	while (find())
	{
		int tmp=inf;
		for (int j=pre[ed];j;j=pre[e[j].s]) tmp=min(tmp,e[j].val);
		fare+=tmp*d[ed];
		flow+=tmp;
		for (int j=pre[ed];j;j=pre[e[j].s]) e[j].val-=tmp,e[j^1].val+=tmp;
	}
}

//zkw最小费用流
int dfs(int now,int flow)
{
	if (now==ed)
	{
		fare+=dis[st]*flow;
		return flow;
	}
	v[now]=1;
	int sap=0;
	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
		{
			int tmp=dfs(k,min(e[j].val,flow-sap));
			e[j].val-=tmp;
			e[j^1].val+=tmp;
			sap+=tmp;
			if (sap==flow)return sap;
		}
	}
	return sap;
}

bool adjust()
{
	int tmp=inf;
	for (int i=st;i<=ed;i++) if (v[i])
		for (int j=fir[i];j;j=e[j].next)
		{
			int k=e[j].t;
			if (!v[k]&&e[j].val) tmp=min(tmp,dis[k]+e[j].cost-dis[i]);
		}
	if (tmp==inf) return 0;
	for (int i=st;i<=ed;i++) if (v[i])
		dis[i]+=tmp;
	return 1;
}

int main()
{
		do{
			do memset(v,0,sizeof(v));
			while (dfs(st,inf));
		}while (adjust());
}

//=======计算几何=======
const double EPS=1e-10;
const double PI=acos(-1.0);

int dcmp(double x){ if (fabs(x)<EPS) return 0; else return x>0 ?1 :-1;}

//=======点与向量=======

struct Point
{
	double x, y;
	Point(){}
	Point(double xx, double yy):x(xx), y(yy){}
	friend bool operator <(Point A, Point B)
	{
		return A.x<B.x || (A.x==B.x && A.y<B.y);
	}
	friend bool operator ==(Point A, Point B)
	{
		return dcmp(A.x-B.x)==0 && dcmp(A.y-B.y)==0;
	}
};
typedef Point Vec;
typedef vector<Point> Points;
typedef vector<Point> Poly;
double AngleOnEarth(Point A,Point B)
{
	double x1=PI*A.x/180.0;
	double y1=PI*A.y/180.0;
	double x2=PI*B.x/180.0;
	double y2=PI*B.y/180.0;
	return acos( cos(x1-x2)*cos(y1)*cos(y2)+sin(y1)*sin(y2) );
}


//向量加法
Vec operator +(Vec a, Vec b){ return Vec(a.x+b.x, a.y+b.y);}

//向量减法
Vec operator -(Point A, Point B){ return Vec(A.x-B.x, A.y-B.y);}

//向量数乘
Vec operator *(Vec a, double k){ return Vec(a.x*k, a.y*k);}

//向量数除
Vec operator /(Vec a, double k){ return Vec(a.x/k, a.y/k);}

//向量点积
double operator ^(Vec a, Vec b){ return a.x*b.x+a.y*b.y;}

//向量叉积
double operator *(Vec a, Vec b){ return a.x*b.y-a.y*b.x;}

//向量长度
double Len(Vec a) { return sqrt(a^a);}

//向量极角
double Ang(Vec a) { return atan2(a.y, a.x);}

//向量与向量夹角
double Ang(Vec a, Vec b) { return acos((a^b)/(Len(a)*Len(b)));}

//三角形有向面积的两倍
double Area2(Point A, Point B, Point C) { return (B-A)*(C-A);}

//向量逆时针旋转rad度
Vec Rotate(Vec a, double rad)
{
	return Vec(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad));
}

//向量的单位方向向量
Vec Orient(Vec a)
{
	double l=Len(a);
	return a/l;
}

//向量的单位法向量
Vec Normal(Vec a)
{
	double l=Len(a);
	return Vec(-a.y/l, a.x/l);
}

//凸包
Poly ConvexHull(Points P)
{
	sort(P.begin(),P.end());
	P.erase(unique(P.begin(),P.end()),P.end());
	int n=P.size();
	Poly St(n+1);
	int m=0;
	for (int i=0;i<n;i++)
	{
		while (m>1 && dcmp((St[m-1]-St[m-2])*(P[i]-St[m-2])) <=0)
			m--;
		St[m++]=P[i];
	}
	int k=m;
	for (int i=n-2;i>=0;i--)
	{
		while (m>k && dcmp((St[m-1]-St[m-2])*(P[i]-St[m-2])) <=0)
			m--;
		St[m++]=P[i];
	}
	if (n>1) St.resize(--m);
	return St;
}

//旋转卡壳
//t为卡壳上顶点，l,r分别为左右顶点
//D为最大直径，S为外接矩形的最小面积，C为最小周长
void RotatingCalipers(Points &P,double &D, double &S, double &C)
{
	P=ConvexHull(P);
	int n=P.size();
	S=C=1e15,D=0;
	int t=1,l=1,r=1;
	for (int i=0;i<n;i++)
	{
		while (dcmp( (P[(i+1)%n]-P[i]) * (P[(t+1)%n]-P[t]) ) > 0) t=(t+1)%n;
		while (dcmp( (P[(i+1)%n]-P[i]) ^ (P[(r+1)%n]-P[r]) ) > 0) r=(r+1)%n;
		if (i==0) l=t;
		while (dcmp( (P[(i+1)%n]-P[i]) ^ (P[(l+1)%n]-P[l]) ) < 0) l=(l+1)%n;
		double h=(P[(i+1)%n]-P[i]) * (P[t]-P[i]) / Len(P[(i+1)%n]-P[i]);
		double w=(P[(i+1)%n]-P[i]) ^ (P[r]-P[l]) / Len(P[(i+1)%n]-P[i]);
		D=max(D,h);
		S=min(S,w*h);
		C=min(C,(w+h)*2);
	}
}

//多边形有向面积
double PolygonArea(Poly P)
{
	double area=0;
	int n=P.size();
	for (int i=1;i<n-1;i++)
		area+=(P[i]-P[0])*(P[i+1]-P[0]);
	return area/2;
}

//多边形周长
double PolygonPerimeter(Poly P)
{
	double len=0;
	int n=P.size();
	for (int i=0;i<n-1;i++)
		len+=Len(P[i+1]-P[i]);
	return len+Len(P[0]-P[n-1]);
}

//=======直线与线段=======

struct Line
{
	Point P;
	Vec v;
	double ang;
	Line(){}
	Line(Point pp, Vec vv):P(pp), v(Orient(vv)), ang(Ang(vv)){}
	friend bool operator <(Line a, Line b)
	{
		return a.ang<b.ang;
	}
	Point point(double k)
	{
		return P+v*k;
	}
};

typedef vector<Line> Lines;

//直线交点(确保唯一)
Point GetIntersection(Line a, Line b)
{
	Point P=a.P, Q=b.P;
	Vec v=a.v, w=b.v;
	Vec u=P-Q;
	double t=(w*u)/(v*w);
	return a.point(t);
}

//点到直线距离
double DistanceToLine(Point P, Line l)
{
	Point A=l.P, B=l.P+l.v;
	Vec u=B-A, v=P-A;
	//不取绝对值得到有向距离
	return fabs((u*v)/Len(u));
}

//点到线段距离
double DistanceToSeg(Point P, Point A, Point B)
{
	if (A==B) return Len(P-A);
	Vec u=B-A, v=P-A, w=P-B;
	if (dcmp(u^v)<0) return Len(v);
	else if (dcmp(u^w)>0) return Len(w);
	else return fabs((u*v)/Len(u));
}

//点在直线上投影
Point GetProjection(Point P, Line l)
{
	Point A=l.P, B=l.P+l.v;
	Vec v=B-A;
	return A+v*((v^(P-A))/(v^v));
}

//判断是否规范相交
bool ProIntersection(Point A1, Point A2, Point B1, Point B2)
{
	double c1=(A2-A1)*(B1-A1);
	double c2=(A2-A1)*(B2-A1);
	double c3=(B2-B1)*(A1-B1);
	double c4=(B2-B1)*(A2-B1);
	return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

//判断点在线段上
bool OnSegment(Point P,Point A1,Point A2)
{
	return dcmp((A1-P)*(A2-P))==0 && dcmp((A1-P)^(A2-P))<0;
}

//点与多边形的位置关系
int InPolygon(Point P,const Poly &Poly)
{
	int cnt=0, n=Poly.size();
	for (int i=0;i<n;i++)
	{
		if (OnSegment(P,Poly[i], Poly[(i+1)%n])) return -1;
		int k=dcmp((Poly[(i+1)%n]-Poly[i])*(P-Poly[i]));
		int d1=dcmp(Poly[i].y-P.y);
		int d2=dcmp(Poly[(i+1)%n].y-P.y);
		if (k>0 && d1<=0 && d2>0) cnt++;
		if (k<0 && d2<=0 && d1>0) cnt--;
	}
	if (cnt!=0)  return 1;
	else return 0;
}

//半平面交
bool OnLeft(Point P,Line l)
{
	return dcmp(l.v*(P-l.P))>=0;
}

Poly HalfPlaneIntersection(vector<Line> l)
{
	Poly Sol;
	Sol.clear();
	int n=l.size();
	sort(l.begin(),l.end());
	int first,last;
	Point *p=new Point[n];
	Line *q=new Line[n];
	q[first=last=0]=l[0];
	for (int i=1;i<n;i++)
	{
		while (first<last && !OnLeft(p[last-1],l[i])) last--;
		while (first<last && !OnLeft(p[first],l[i])) first++;
		q[++last]=l[i];
		if (dcmp(q[last].v*q[last-1].v)==0)
		{
			last--;
			if (OnLeft(l[i].P,q[last])) q[last]=l[i];
		}
		if (first<last) p[last-1]=GetIntersection(q[last-1], q[last]);
	}
	while (first<last && !OnLeft(p[last-1],q[first])) last--;
	if (last-first<=1) return Sol;
	p[last]=GetIntersection(q[last], q[first]);
	for (int i=first;i<=last;i++) Sol.push_back(p[i]);
	return Sol;
}

//=======圆相关=======

struct Circle
{
	Point O;
	double r;
	Circle(Point O,double r):O(O),r(r){}
	Point point(double rad)
	{
		return Point(O.x+r*cos(rad), O.y+r*sin(rad));
	}
};

//圆和直线交点(方程法)
Points GetIntersection(Line L, Circle C, double &t1, double &t2)
{
	Points Sol; Sol.clear();
	double a=L.v.x, b=L.P.x-C.O.x, c=L.v.y, d=L.P.y-C.O.y;
	double e=a*a+c*c, f= 2*(a*b+c*d), g=b*b-C.r*C.r;
	double delta=f*f-4*e*g;
	if (dcmp(delta)<0) return Sol;
	if (dcmp(delta)==0)
	{
		t1=t2=-f/(2*e);
		Sol.push_back(L.point(t1));
	}
	else//相交
	{
		t1=(-f-sqrt(delta))/(2*e);
		Sol.push_back(L.point(t1));
		t2=(-f+sqrt(delta))/(2*e);
		Sol.push_back(L.point(t2));
	}
	return Sol;
}

//圆和直线交点(几何法)
Points GetIntersection(Line L, Circle C)
{
	Points Sol; Sol.clear();
	double d=DistanceToLine(C.O, L);
	if (dcmp(d-C.r)>0) return Sol;//相离
	Point ans=GetIntersection(L,Line(C.O,Normal(L.v)));
	if (dcmp(d-C.r)==0)
		Sol.push_back(ans);
	else
	{
		double len=sqrt(C.r*C.r-d*d);
		Vec v=Orient(L.v);
		Sol.push_back(ans+v*len);
		Sol.push_back(ans-v*len);
	}
	return Sol;
}

//圆与圆的交点
Points GetIntersection(Circle C, Circle D)
{
	Vec v=D.O-C.O;
	Points Sol; Sol.clear();
	double d=Len(v);
	if (dcmp(C.r-D.r)>0) swap(C,D);
	if (dcmp(d)==0 || dcmp(C.r+D.r-d) <0 || dcmp(D.r-C.r-d) >0) return Sol;//同心 | 外离 | 内含
	if (dcmp(C.r+D.r-d)==0 || dcmp(D.r-C.r-d)==0)//相切
		Sol.push_back(C.O+Orient(v)*C.r);
	else//相交
	{
		double rad=Ang(v);
		double th=acos((C.r*C.r+d*d-D.r*D.r)/(2*C.r*d));
		Point P=C.point(rad+th);
		Point Q=C.point(rad-th);
		Sol.push_back(P);
		Sol.push_back(Q);
	}
	return Sol;
}

//过点P到圆C的切线
Lines GetTangents(Point P,Circle C)
{
	Vec v=C.O-P,tmp;
	Lines Sol; Sol.clear();
	double d=Len(v);
	if (d<C.r) return Sol;
	if (dcmp(d-C.r)==0)
		Sol.push_back(Line(P,Normal(v)));
	else
	{
		double rad=asin(C.r/d);
		Sol.push_back(Line(P,Rotate(v,rad)));
		Sol.push_back(Line(P,Rotate(v,-rad)));
	}
	return Sol;
}

//两圆公切线
Lines GetTangents(Circle C, Circle D)
{
	Point A,B;
	Lines Sol; Sol.clear();
	if (dcmp(C.r-D.r)<0) swap(C, D);
	double dd=(C.O.x-D.O.x)*(C.O.x-D.O.x)+(C.O.y-D.O.y)*(C.O.y-D.O.y);
	double rdif=C.r-D.r;
	double rsum=C.r+D.r;
	if (dcmp(dd-rdif*rdif)<0) return Sol;//内含
	if (dcmp(dd)==0 && dcmp(C.r-D.r)==0) return Sol;//重合
	double rad=atan2(D.O.y-C.O.y,D.O.x-C.O.x);
	if (dcmp(dd-rdif*rdif)==0)//内切
	{
		A=C.point(rad), B=D.point(rad);
		Sol.push_back(Line(A,B-A));
		//Sol.push_back(Line(A,Normal(C.O-D.O)));
		return Sol;
	}
	double th=acos((C.r-D.r)/sqrt(dd));
	A=C.point(rad+th), B=D.point(rad+th);
	Sol.push_back(Line(A,B-A));
	A=C.point(rad-th), B=D.point(rad-th);
	Sol.push_back(Line(A,B-A));
	if (dcmp(dd-rsum*rsum)==0)//外切
	{
		A=C.point(rad), B=D.point(rad+PI);
		Sol.push_back(Line(A,B-A));
		//Sol.push_back(Line(A,Normal(D.O-C.O)));
	}
	else if (dcmp(dd-rsum*rsum)>0)//相离
	{
		double ro=acos((C.r+D.r)/sqrt(dd));
		A=C.point(rad+ro), B=D.point(PI+rad+ro);
		Sol.push_back(Line(A,B-A));
		A=C.point(rad-ro), B=D.point(PI+rad-ro);
		Sol.push_back(Line(A,B-A));
	}
	return Sol;
}

//=======其他=======

//三分求最小值
double l=mi,r=mx,ans;
while (dcmp(l-r)<=0)
{
	double lmid=l+(r-l)/3.0;
	double rmid=r-(r-l)/3.0;
	if (dcmp(get_ans(lmid)-get_ans(rmid))<=0)
	{
		r=rmid-eps;
		ans=get_ans(lmid);
	}
	else
	{
		l=lmid+eps;
	}	
}
//莫队算法
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define maxn 55000
#define inf 2147483647
using namespace std;
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

//整体二分
void add(int x,int y)
{
    for (int i=x;i<=n;i+=(i&-i)) t[i]+=y;
}

int ask(int x)
{
    int tmp=0;
    for (int i=x;i>0;i-=(i&-i)) tmp+=t[i];
    return tmp;
}

void divide(int head,int tail,int l,int r)
{
    //cout<<head<<' '<<tail<<' '<<l<<' '<<r<<endl;
    if (head>tail) return ;
    if (l==r) 
    {
        for (int i=head;i<=tail;i++)
            if (q[i].tp==3) ans[q[i].s]=l;//,cout<<l<<endl;
        return ;
    }
    int mid=(l+r)>>1;
    for (int i=head;i<=tail;i++)
    {
        if (q[i].tp==1&&q[i].y<=mid) add(q[i].x,1);
        else
        if (q[i].tp==2&&q[i].y<=mid) add(q[i].x,-1);
        else
        if (q[i].tp==3) tmp[i]=ask(q[i].y)-ask(q[i].x-1);
    }
    for (int i=head;i<=tail;i++)
    {
        if (q[i].tp==1&&q[i].y<=mid) add(q[i].x,-1);
        else
        if (q[i].tp==2&&q[i].y<=mid) add(q[i].x,1);
    }
    int l1=0,l2=0;
    for (int i=head;i<=tail;i++)
        if (q[i].tp==3)
        {
            if (q[i].cur+tmp[i]>q[i].k-1)//q[i].cur+tmp[i]表示累积了多少个数
                q1[++l1]=q[i];
            else
            {
                q[i].cur+=tmp[i];
                q2[++l2]=q[i];
            }
        }
        else
        {
            if (q[i].y<=mid) q1[++l1]=q[i];
            else q2[++l2]=q[i];
        }
    for (int i=1;i<=l1;i++) q[head+i-1]=q1[i];
    for (int i=1;i<=l2;i++) q[head+l1+i-1]=q2[i];
    divide(head,head+l1-1,l,mid);
    divide(head+l1,tail,mid+1,r);
}    

//手动开栈
VS(C++):
#pragma comment(linker, "/STACK:102400000,102400000")

G++:
int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p));
//__asm__("movl %0, %%rsp\n" :: "r"(p));


//对拍
:loop
datamaker.exe
a1.exe a2.exe
fc a1.out a2.out
if %errorlevel%==1 pause
goto loop