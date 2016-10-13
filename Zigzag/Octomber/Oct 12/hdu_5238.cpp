#include <bits/stdc++.h>
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
#define maxn 100200
using namespace std;

const int mod[4]={7,13,17,19};
const int oo=29393;
int origin[7][13][17][19];
int f[maxn<<3][4][20];
int n,m;
void update(int x)
{
	for (int i=0;i<4;i++)
		for (int j=0;j<mod[i];j++)
			f[x][i][j]=f[x<<1|1][i][f[x<<1][i][j]];
}

void change(int x, int sign, int z)
{
	for (int i=0;i<4;i++)
		for (int j=0;j<mod[i];j++)
		{
			if (sign=='+')
				f[x][i][j]=(j+z)%mod[i];
			else if (sign=='*')
				f[x][i][j]=(j*z)%mod[i];
			else
			{
				int tmp=1;
				for (int k=1;k<=z%(mod[i]-1);k++)
					tmp=tmp*j%mod[i];
				f[x][i][j]=tmp;
			}
		}
}

void modify(int x, int l, int r, int pos, char sign, int z)
{
	if (l==r)
	{
		change(x, sign, z);
		return ;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) modify(lson, pos, sign, z);
	else modify(rson, pos, sign, z);
	update(x);
}

void init()
{
	for (int x=1;x<(n<<3);x++)
		for (int i=0;i<4;i++)
			for (int j=0;j<mod[i];j++)
				f[x][i][j]=j;
}

void prepare()
{
	for (int i=oo-1;i>=0;i--)
		origin[i%mod[0]][i%mod[1]][i%mod[2]][i%mod[3]]=i;
}

int main()
{
	int Case;
	scanf("%d",&Case);
	prepare();
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&n,&m);
		init();
		char c;
		int x, y, z;
		for (int i=1;i<=n;i++)
		{
			scanf(" %c%d",&c,&z);
			modify(1,1,n,i,c,z);
			// cout<<1<<endl;
			// for (int i=0;i<4;i++)
			// 	for (int j=0;j<mod[i];j++)
			// 		cout<<i<<' '<<j<<' '<<f[1][i][j]<<endl;
		}
		int st;
		printf("Case #%d:\n",o);
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&y);
			if (y==1)
			{
				scanf("%d",&st);
				//cout<<st<<endl;
				int w=f[1][0][st%mod[0]];
				int x=f[1][1][st%mod[1]];
				int y=f[1][2][st%mod[2]];
				int z=f[1][3][st%mod[3]];
				//cout<<w<<' '<<x<<' '<<y<<' '<<z<<endl;
				printf("%d\n",origin[w][x][y][z]);
			}
			else
			{
				scanf("%d %c%d",&x,&c,&z);
				modify(1,1,n,x,c,z);
			}
		}
	}
	return 0;
}
