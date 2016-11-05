#include <bits/stdc++.h>
using namespace std;

#define maxn 202020

struct bitup{
	int mx[maxn];
	int num;
	void init(int n){
		num=n;
		memset(mx,0,sizeof(mx));
	}
	void add(int x, int z){
		for (int i=x;i<=num;i+=(i&-i))
			mx[i]=max(mx[i], z);
	}
	int ask(int x){
		int tmp=0;
		for (int i=x;i>=1;i-=(i&-i))
			tmp=max(tmp, mx[i]);
		return tmp;
	}
}s,t;

int a[maxn], up[maxn], dw[maxn];
int n;

int main()
{
	freopen("improvements.in","r",stdin);
	freopen("improvements.out","w",stdout);
	scanf("%d",&n);
	int x;
	for (int i=1;i<=n;i++){
		scanf("%d",&x);
		a[x]=i;
	}
	//for (int i=1;i<=n;i++) cout<<a[i]<<' '; cout<<endl;
	s.init(n+1);
	t.init(n+1);
	for (int i=1;i<=n;i++){
		up[i]=s.ask(a[i])+1;
		s.add(a[i], up[i]);
	}
	for (int i=n;i>=1;i--){
		dw[i]=t.ask(a[i])+1;
		t.add(a[i], dw[i]);
	}
	int ans=0;
	for (int i=1;i<=n;i++){
		ans=max(ans, up[i]+dw[i]-1);
	}
	printf("%d\n",ans);

	return 0;
}