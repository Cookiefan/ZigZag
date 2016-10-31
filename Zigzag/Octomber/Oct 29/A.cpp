#include <bits/stdc++.h>
using namespace std;
#define maxn 300200
#define inf 2000000000

struct mi_bit{
	int mi[maxn];
	int num;
	mi_bit(){}
	mi_bit(int n):num(n){}
	void clear(){
		for (int i=0;i<=num;i++)
			mi[i]=inf;
	}
	void add(int x, int z){
		for (int i=x;i<=num;i+=(i&-i))
			mi[i]=min(mi[i], z);
	}
	int ask(int x){
		int tmp=inf;
		for (int i=x;i>=1;i-=(i&-i))
			tmp=min(tmp, mi[i]);
		return tmp;
	}
};
struct mx_bit{
	int mx[maxn];
	int num;
	mx_bit(){}
	mx_bit(int n):num(n){}
	void clear(){
		for (int i=0;i<=num;i++)
			mx[i]=-inf;
	}
	void add(int x, int z){
		for (int i=x;i<=num;i+=(i&-i))
			mx[i]=max(mx[i], z);
	}
	int ask(int x){
		int tmp=-inf;
		for (int i=x;i>=1;i-=(i&-i))
			tmp=max(tmp, mx[i]);
		return tmp;
	}
};

struct tii{
	int x, y, z;
};

int a[maxn], pre[maxn], suf[maxn];
int pool[maxn];
int n;

int getnum(int x){
	int tmp=lower_bound(pool, pool+n, x)-pool+1;
	return tmp;
}

int main()
{
	//freopen("A.in","r",stdin);
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	for (int i=0;i<n;i++) pool[i]=a[i];
	sort(pool, pool+n);
	for (int i=0;i<n;i++) a[i]=getnum(a[i]);

	for (int i=0;i<n;i++) a[n+i]=a[i];
	for (int i=0;i<n;i++) a[2*n+i]=a[i];


	mx_bit s(3*n);
	s.clear();
	for (int i=0;i<n;i++)
		s.add(a[i], i);
	for (int i=n;i<2*n;i++){
		pre[i]=s.ask(a[i]-1);
		s.add(a[i], i);
	}

	mi_bit t(3*n);
	t.clear();
	for (int i=3*n-1;i>=2*n;i--)
		t.add(a[i], i);
	for (int i=2*n-1;i>=n;i--){
		suf[i]=t.ask(a[i]-1);
		t.add(a[i], i);
	}

	int ans=inf;
	tii p;
	for (int i=n;i<2*n;i++){
		if (suf[i]==inf || pre[i]==-inf) continue;
		int tmp=suf[i]-pre[i];
		if (tmp<ans){
			ans=tmp;
			p=(tii){pre[i]%n, i%n, suf[i]%n};
		}
	}
	printf("%d %d %d\n",p.x+1, p.y+1, p.z+1);
	return 0;
}