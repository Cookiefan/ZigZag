#include <bits/stdc++.h>
#define maxn 2200
#define maxm 22200
#define inf 9999999999999999
using namespace std;

using namespace std;
struct et
{
    int s,t,next;
    long long val,cost;
}e[maxm];
int fir[maxn],v[maxn];
long long dis[maxn];
bool inque[maxn];
int tot,st,ed;
long long ans;

int dfs(int now,long long flow)
{
    if (now==ed)
    {
        ans+=(long long)dis[st]*flow;
        return flow;
    }
    long long sap=0;    v[now]=1;
    for (int j=fir[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (!v[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
        {
            int tmp=dfs(k,min(e[j].val,flow-sap));
            e[j].val-=tmp;
            e[j^1].val+=tmp;
            sap+=tmp;
            if (sap==flow) return sap;
        }
    }
    return sap;
}

bool adjust()
{
    long long tmp=inf;
    for (int i=st;i<=ed;i++) if (v[i])
        for (int j=fir[i];j;j=e[j].next)
        {
            int k=e[j].t;
            if (!v[k] && e[j].val) tmp=min(tmp,dis[k]+e[j].cost-dis[i]);
        }
    if (tmp==inf) return 0;
    for (int i=st;i<=ed;i++) if (v[i])
        dis[i]+=tmp;
    return 1;
}

void add(int x,int y,long long z,long long w)
{
    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
    e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

class MoveStones
{
public:
	long long get(vector<int> a, vector<int>b)
	{
		vector<int>c ;
		int n=a.size();
		for (int i=0;i<n;i++) c.push_back(a[i]-b[i]);
		long long sum=0;
		for (int i=0;i<n;i++) sum+=c[i];
		if (sum!=0) return -1;
		st=0,ed=n+1,tot=1;
		for (int i=1;i<=n;i++)
		{
			if (c[i-1]>0) add(st,i,c[i-1],0);
			else add(i,ed,-c[i-1],0);
			if (i==1) add(i,n,inf,1); else add(i,i-1,inf,1);
			if (i==n) add(i,1,inf,1); else add(i,i+1,inf,1);
		}
		//for (int i=2;i<=tot;i+=2) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
		ans=0;
		do 
        	do memset(v,0,sizeof(v));
        	while (dfs(st,inf));
    	while (adjust());
		return ans;
	}
};

int main()
{
	MoveStones S;
	int n,x;
	scanf("%d",&n);
	vector<int> a,b;
	for (int i=0;i<n;i++) scanf("%d",&x), a.push_back(x);
	for (int i=0;i<n;i++) scanf("%d",&x), b.push_back(x);
	printf("%lld\n",S.get(a,b));
	return 0;
}