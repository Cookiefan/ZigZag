#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define maxnum 10000002
using namespace std;
deque<int> que;
vector<int> num;
int vis[maxnum];
int s,t;

vector<int> trans(int x)
{
	vector<int> tmp;
	tmp.clear();
	for (int i=0;i<6;i++)
	{
		tmp.push_back(x%10);
		x/=10;
	}
	reverse(tmp.begin(),tmp.end());
	return tmp;
}

int trans(vector<int> y)
{
	int tmp=0;
	for (int i=0;i<6;i++)
		tmp=tmp*10+y[i];
	return tmp;
}

int step(int s,int t)
{
	que.clear();
	memset(vis,-1,sizeof(vis));
	que.push_back(s*10);
	vis[s*10]=0;
	while (!que.empty())
	{
		int now=que.front();
		que.pop_front();
		if (now/10==t) return vis[now];
		// cout<<now<<' '<<vis[now]<<endl;
		// getchar();
		for (int i=1;i<=6;i++)
		{	
			num=trans(now/10);
			int pos=now%10;
			// for (int j=0;j<6;j++) cout<<num[j]<<' ';
			// 	cout<<endl;
			switch(i)
			{
				case 1:
				{
					if (pos==0) break;
					swap(num[pos],num[pos-1]);
					break;
				}
				case 2:
				{
					if (pos==5) break;
					swap(num[pos],num[pos+1]);
					break;
				}
				case 3:
				{
					if (pos==0) break;
					pos--;
					break;
				}
				case 4:
				{
					if (pos==5) break;
					pos++;
					break;
				}
				case 5:
				{
					if (num[pos]==9) break;
					num[pos]++;
					break;
				}
				case 6:
				{
					if (num[pos]==0) break;
					num[pos]--;
					break;
				}
			}
			int tmp=trans(num);
			if (vis[tmp*10+pos]==-1)
			{
				// cout<<now<<endl;
				// getchar();
				que.push_back(tmp*10+pos); 
				vis[tmp*10+pos]=vis[now]+1;
			}
		}
	}
}

int main()
{
	int Case;
	scanf("%d",&Case);
	for (int o=1;o<=Case;o++)
	{
		scanf("%d%d",&s,&t);
		printf("%d\n",step(s,t));
	}
	return 0;
}