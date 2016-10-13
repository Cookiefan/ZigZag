#include <bits/stdc++.h>
#define maxn 100200
using namespace std;

map<int,int>ax,ay;
typedef pair<int,int> pii;
map<pii,int> mp;

int n,m,p,num,tot;

int main()
{
	//freopen("G.in","r",stdin);
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d%d",&n,&m,&p);
		int x, y, z;
		ax.clear(); ay.clear();
		num=0;
		for (int i=1;i<=p;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			if (!ax.count(x)) ax[x]=x;
			if (!ay.count(y)) ay[y]=y;
			// cout<<x<<' '<<y<<' '<<ax[x]<<' '<<ay[y]<<endl;
			mp[pii(x, y)]=z;
		}
		scanf("%d",&tot);
		int sign, l, r;
		printf("Case #%d:\n",o);
		for (int i=1;i<=tot;i++)
		{
			scanf("%d%d%d",&sign,&l,&r);
			if (sign==1)
			{
				if (!ax.count(l) && !ax.count(r)) continue;
				x=ax[l]; y=ax[r];
				ax[l]=y; ax[r]=x;
				//swap(ax[l], ax[r]);
			}
			else if (sign==2)
			{
				if (!ay.count(l) && !ay.count(r)) continue;
				x=ay[l]; y=ay[r];
				ay[l]=y; ay[r]=x;
				//swap(ay[l], ay[r]);
			}
			else
			{
				if (!ax.count(l) && !ay.count(r)) printf("%d\n",0);
				else
				{
					x=ax[l]; y=ay[r];
					printf("%d\n",mp[pii(x,y)]);
				}
			}
		}
	}
	return 0;
}