#include <bits/stdc++.h>
#define maxn 2200
using namespace std;
typedef long long LL;
int n;
int dam[maxn], rec[maxn];
vector<int> nxt[maxn];

bool cmp(int a, int b){
	if ((rec[a]-dam[a])<0&&(rec[b]-dam[b])>=0||(rec[a]-dam[a])>=0&&(rec[b]-dam[b])<0){
		return rec[a]-dam[a]>=0;
	}
	else{
		if (rec[a]>=dam[a]) return dam[a]<dam[b];
		else return rec[a]>rec[b];
	}
}

void solve(int x){
	for (int y:nxt[x]){
		solve(y);
	}
	sort(nxt[x].begin(), nxt[x].end(), cmp);
	//for (int y:nxt[x]) cout<<y<<": "<<dam[y]<<','<<rec[y]<<"   "; cout<<endl;
	int now=-dam[x], mi=now;
	for (int y:nxt[x]){
		now=now-dam[y];
		mi=min(mi, now);
		now=now+rec[y];
		mi=min(mi, now);
	}
	now+=rec[x];
	mi=min(mi, now);
	now-=dam[x];
	mi=min(mi, now);
	dam[x]=-mi;
	rec[x]=dam[x]+now;
}

int main()
{
	scanf("%d",&n);
	int x, y, z, p;
	for (int i=1;i<=n;i++){
		scanf("%d",&x);
		dam[i]=x;
		nxt[i].clear();
		scanf("%d",&p);
		if (!p){
			scanf("%d",&y);
			rec[i]=y;
		}
		else{
			rec[i]=0;
			for (int j=1;j<=p;j++){
				scanf("%d",&y);
				nxt[i].push_back(y);
			}
		}
	}
	solve(1);
	printf("%d\n", dam[1]);
	return 0;
}
// 16
// 7 1 2
// 17 5 9 8 6 4 7
// 10 1 10
// 7 2 5 3
// 11 0 0
// 10 0 16
// 16 0 0
// 16 0 0
// 5 0 7
// 13 1 11
// 400 3 12 15 16
// 100 0 800
// 400 0 1100
// 300 0 2300
// 800 0 1100
// 1000 2 13 14
// Participant's output
// 1654
// Jury's answer
// 1154

