#include <bits/stdc++.h>
#define maxn 66
using namespace std;

const int ms=52;
struct matrix{
	double e[ms][ms];
	matrix(){memset(e,0,sizeof(e));}
	matrix(double x){
		memset(e,0,sizeof(e));
		for (int i=0;i<ms;i++)
			e[i][i]=x;
	}
	friend matrix operator *(matrix a, matrix b){
		matrix c;
		for (int k=0;k<ms;k++)
			for (int i=0;i<ms;i++)
				for (int j=0;j<ms;j++)
					c.e[i][j]+=a.e[i][k]*b.e[k][j];
		return c;
	};
	friend matrix operator ^(matrix a, int b){
		matrix tmp=matrix(1);
		while (b){
			if (b&1) tmp=tmp*a;
			a=a*a;
			b=b>>1;
		}
		return tmp;
	};
};

int n,m,k;
vector<int> t[maxn];
double ans[maxn];

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&k);
		matrix T;
		int x, y;
		for (int i=1;i<=n;i++)
			t[i].clear();
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			t[x].push_back(y);
			t[y].push_back(x);
		}
		for (int x=1;x<=n;x++)
			for (int y:t[x])
				T.e[x][y]=1.0/t[x].size();
		
		memset(ans,0,sizeof(ans));
		for (int p=1;p<=n;p++)
		{
			matrix R=T;
			for (int i=1;i<=n;i++)
				R.e[p][i]=0;
			matrix S;
			for (int i=1;i<=n;i++)
				S.e[1][i]=1.0/n;
			R=R^k;
			S=S*R;
			for (int i=1;i<=n;i++)
				if (i!=p)
					ans[p]+=S.e[1][i];
		}
		for (int i=1;i<=n;i++)
			printf("%.6f\n",ans[i]);
	}

	return 0;
}