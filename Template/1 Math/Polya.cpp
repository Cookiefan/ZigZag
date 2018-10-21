//polya
#include <bits/stdc++.h>
#define maxn 
using namespace std;
typedef vector<int> state;
typedef long long LL;
map<state, int> mp;
state flip[4];
vector<int> col;
LL n, oo;

LL mul( LL x, LL y, LL p )
{
    LL tmp=((LL)((double)x*y/p+1e-6 )*p);
    return x*y - tmp;
}

LL exp(LL a, LL b, LL p)
{
	a%=p;
	LL tmp=1;
	while (b)
	{
		if (b&1) tmp = mul(tmp, a, p);;
		a=mul(a, a, p);
		b=b/2;
	}
	return tmp;
}

void write(state t){
	for (int j=0;j<t.size();j++)
		cout<<t[j]<<' ';
	cout<<endl;
}

state operator *(state a, state b){
	state c;
	for (int k=0;k<30;k++)
		c.push_back(b[a[k]]);
	return c;
}

int vis[32];

int cal(state s){
	memset(vis, 0, sizeof(vis));
	int sum=0;
	for (int i=0;i<30;i++)
		if (!vis[i]){
			sum++;
			int tmp=i;
			do{
				vis[tmp]=1;
				tmp=s[tmp];
			}while (tmp!=i);
		}
	return sum;
}

int dfs(state s){
	mp[s]=cal(s);
	// cout<<mp.size()<<endl;
	col.push_back(mp[s]);
	for (int i=0;i<3;i++){
		state t = s*flip[i];
		if (mp.count(t)==0){
			dfs(t);
		}
	}
}

int main()
{
	int a[4][30]={
	{0,1,17,3,4,14,6,7,11,9,10,8,12,13,5,15,16,2,18,19,24,23,22,21,20,25,26,27,28,29},
	{15,16,17,12,13,14,9,10,11,6,7,8,3,4,5,0,1,2,26,25,24,23,22,21,20,19,18,29,28,27},
	{6,3,0,7,4,1,8,5,2,15,12,9,16,13,10,17,14,11,27,28,29,18,19,20,21,22,23,24,25,26},
	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}};
	for (int i=0;i<4;i++){
		flip[i].insert(flip[i].begin(), a[i], a[i]+30);
	}
	col.clear();
	dfs(flip[3]);
	sort(col.begin(), col.end());
	// write(col);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++){
		scanf("%d%d",&n,&oo);
		LL ans=0, bp=(LL)oo*col.size();
		//当oo不是质数时,用oo*b代替oo,得到的答案一定能整除b
		for (int i=0;i<col.size();i++){
			ans+=exp(n, col[i], bp);
			ans%=bp;
		}
		ans = ans/col.size();
		cout<<ans<<endl;
	}		
	return 0;
}
