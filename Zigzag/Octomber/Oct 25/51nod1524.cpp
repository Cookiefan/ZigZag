#include <bits/stdc++.h>
using namespace std;
#define maxn 1000200
int read() {
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}
int f[maxn], a[maxn], v[maxn];
int n;
int main()
{

	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		a[i]=read();
		v[a[i]]=i;
	}
	sort(a+1, a+n+1);
	int ans=0;
	for (int i=1;i<=n;i++){
		f[a[i]]+=1;
		ans=max(ans, f[a[i]]);
		for (int x=2;a[i]*x<=a[n];x++)
			if (v[a[i]*x]){
				f[a[i]*x]=max(f[a[i]*x], f[a[i]]);
			}
	}
	printf("%d\n",ans);
	return 0;
}