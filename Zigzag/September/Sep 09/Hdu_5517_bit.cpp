#include <bits/stdc++.h>
#define maxn 100
using namespace std;

struct bit
{
	int sum[maxn][maxn];
	int nx, ny;
	bit(){}
	bit(int nx, int ny):nx(nx), ny(ny){
		memset(sum,0,sizeof(sum));
	}
	void clear(){
		memset(sum,0,sizeof(sum));
	}
	void add(int x, int y, int z){
		for (int i=x;i<=nx;i+=(i&-i))
			for (int j=y;j<=ny;j+=(j&-j))
				sum[i][j]+=z;
	}
	int ask(int x, int y){
		int tmp=0;
		for (int i=x;i>=1;i-=(i&-i))
			for (int j=y;j>=1;j-=(j&-j))
				tmp+=sum[i][j];
		return tmp;
	}
};

int vy[maxn*100];
struct tii
{
	int x, y, z;
	tii(){}
	tii(int x, int y, int z):x(x), y(y), z(z){}
	friend bool operator <(tii a, tii b){
		return a.x>b.x;
	};
};
vector<tii> C;

int n,m;

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		int x, y, z;
		C.clear();
		memset(vy,0,sizeof(vy));
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			vy[y]=max(vy[y], x);
		}
		for (int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			C.push_back(tii(vy[z], x, y));
		}
		sort(C.begin(), C.end());
		bit S(50, 50);
		int ans=0;
		for (tii e:C)
		{
			if (S.ask(e.y, e.z)==0)
				ans++;
			S.add(e.y, e.z, 1);
		}
		printf("Case #%d: %d\n", o, ans);
	}
	
	return 0;
}