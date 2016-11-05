#include <bits/stdc++.h>
using namespace std;
#define maxn 1020

int a[maxn];
map<int,int> filter[maxn];
char s[maxn];
typedef bitset<maxn> bs;
typedef long long LL;
bs data[maxn];
int n,m,len,p;
vector<int> ans;

bool judge(int k){
	for (int i=0;i<p;i++){
		int flag=1;
		for (auto x:filter[i])
			if (data[k][x.first]==0){
				flag=0;
				break;
			}
		if (flag) return 1;
	}
	return 0;
}

int getnum(char c){
	if (isdigit(c))
		return c-'0';
	else
		return 10+c-'a';
}

int main()
{
	freopen("filter.in","r",stdin);
	freopen("filter.out","w",stdout);

	scanf("%d%d",&len,&m);
	for (int i=0;i<m;i++) scanf("%d",&a[i]);
	scanf("%d",&n);
	int x;
	for (int i=0;i<n;i++){
		scanf("%s",s);
		int k=0;
		data[i].reset(0);
		for (int j=0;j<=len/4;j++){
			x=getnum(s[j]);
			for (int l=0;l<4&&k<len;l++){
				data[i][k++]=x&1;
				x>>=1;
			}
		}
		//for (int j=0;j<len;j++) cout<<data[i][j]; cout<<endl;
	}

	scanf("%d",&p);
	for (int i=0;i<p;i++){
		scanf("%d",&x);
		filter[i].clear();
		for (int j=0;j<m;j++)
			filter[i][(LL)x*a[j]%len]=1;
	}

	ans.clear();
	for (int i=0;i<n;i++)
		if (judge(i))
			ans.push_back(i);
	printf(ans.size()?"%d ":"%d\n",ans.size());
	for (int i=0;i<ans.size();i++)
		printf(i==ans.size()-1?"%d\n":"%d ",ans[i]);

	return 0;
}