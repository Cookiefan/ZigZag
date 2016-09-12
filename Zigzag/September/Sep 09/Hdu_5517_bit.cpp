#include <bits/stdc++.h>
#define maxn 1020
using namespace std;
typedef long long LL;
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
		for (int i=x;i>=1;i-=(i&-i))
			for (int j=y;j>=1;j-=(j&-j))
				sum[i][j]+=z;
	}
	int ask(int x, int y){
		int tmp=0;
		for (int i=x;i<=nx;i+=(i&-i))
			for (int j=y;j<=ny;j+=(j&-j))
				tmp+=sum[i][j];
		return tmp;
	}
};

int vy[maxn*100], sy[maxn*100];
struct tii
{
	int x, y, z;
	tii(){}
	tii(int x, int y, int z):x(x), y(y), z(z){}
	friend bool operator <(tii a, tii b){
		return a.x==b.x?a.y==b.y?a.z>b.z:a.y>b.y:a.x>b.x;
	};
};
map<tii, LL> C;


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
			if (x>vy[y])
			{
				vy[y]=x;
				sy[y]=1;
			}
			else if (x==vy[y])
				sy[y]++;
		}
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			tii tmp=tii(vy[z], x, y);
			if (!C.count(tmp)) C[tmp]=0;
			C[tmp]+=sy[z];
		}
		// for (auto e:C)
		// 	cout<<e.first.x<<' '<<e.first.y<<' '<<e.first.z<<' '<<e.second<<endl;
		bit S(1020, 1020);
		LL ans=0;
		for (auto e:C)
		{
			if (S.ask(e.first.y, e.first.z)==0)
				ans+=e.second;
			S.add(e.first.y, e.first.z, 1);
		}
		printf("Case #%d: %I64d\n", o, ans);
	}
	
	return 0;
}