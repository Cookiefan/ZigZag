#include <bits/stdc++.h>
using namespace std;
#define maxn 50200
#define maxm 1066
#define inf 999999999

typedef long long LL;
int col[maxn];
LL sum[maxm];
int size[maxn], mxsize[maxn], vis[maxn], msk[maxn];
int n,m,rot;
vector<int> q;
LL ans;

vector<int> t[maxn];

int rev(int x){
	for (int i=0;i<m;i++)
		x=x^(1<<i);
	return x;
}

void chose(int x, int fa, int num){
	size[x]=1; mxsize[x]=0;
	for (int j=0;j<t[x].size();j++){
		int y=t[x][j];
		if (!vis[y] && y!=fa){
			chose(y,x,num);
			size[x]+=size[y];
			mxsize[x]=max(mxsize[x], size[y]);
		}
	}
	mxsize[x]=max(mxsize[x], num-size[x]);
	if (mxsize[x]<mxsize[rot]) rot=x;
}

int chose_rot(int x, int num){
	rot=0;
	chose(x, 0, num);
	return rot;
}

void get_mask(int x, int fa){
	q.push_back(msk[x]);
	for (int j=0;j<t[x].size();j++){
		int y=t[x][j];
		if (!vis[y] && y!=fa){
			msk[y]=msk[x]|(1<<(col[y]-1));
			get_mask(y, x);
		}
	}
}

bool cmp(int x, int y){
	return x>y;
}

LL get_ans(int x, int h){
	//cout<<"x:  "<<x<<endl;
	q.clear();
	msk[x]=h;
	get_mask(x, 0);
	memset(sum,0,sizeof(sum));
	for (int i=0;i<q.size();i++){
		//cout<<q[i]<<' ';
		sum[q[i]]++;
	}
	//sort(q.begin(), q.end(), cmp);
	for (int j=0;j<m;j++)
		for (int cnt=(1<<m)-1;cnt>=0;cnt--){
			if ((cnt>>j) &1)
				sum[cnt^(1<<j)]+=sum[cnt];
		}
	LL tmp=0;
	for (int i=0;i<q.size();i++){
		//cout<<q[i]<<' '<<rev(q[i])<<' '<<sum[rev(q[i])]<<endl;
		tmp+=sum[rev(q[i])];
	}
	//cout<<tmp<<endl;
	return tmp;
}

void solve(int x){
	vis[x]=1;
	ans+=get_ans(x, 1<<(col[x]-1));
	for (int j=0;j<t[x].size();j++){
		int y=t[x][j];
		if (!vis[y]){
			ans-=get_ans(y, msk[y]);
			solve(chose_rot(y, size[y]));
		}
	}
}

void init(){
	for (int i=1;i<=n;i++) t[i].clear();
	memset(vis,0,sizeof(vis));
	ans=0;
	mxsize[0]=inf;
}

int main()
{
	//freopen("G.in","r",stdin);
	while (scanf("%d%d",&n,&m)!=EOF){
		init();
		for (int i=1;i<=n;i++) scanf("%d",&col[i]);
		int x, y;
		for (int i=1;i<n;i++){
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			t[y].push_back(x);
		}
		ans=0;
		solve(chose_rot(1,n));
		printf("%lld\n",ans);
	}
	return 0;
}