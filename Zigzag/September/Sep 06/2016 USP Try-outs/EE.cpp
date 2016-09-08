#include <bits/stdc++.h>
using namespace std;
const int N = 312, K = 15, E = 10;
#define fst first
#define snd second
typedef pair<int, int> pii;
map<char, int> tr[N];
int f[N], mrk[N], en = 1, bad[N];
char s[N];
int M[N][E];
char ch[N][1 << K];
pii ls[N][1 << K];

int main() {
	int i, j, k, m;
	scanf("%d %d", &k, &m);
	for(j = 0; j < k + m; j++) {
		scanf("%s", s);
		int v = 0;
		for(i = 0; s[i]; i++) {
			if(!tr[v][s[i]]) tr[v][s[i]] = en++;
			v = tr[v][s[i]];
		}
		if(j < k) mrk[v] |= (1 << j);
		else bad[v] = 1;
	}
	{
		queue<int> q;
		for(auto e : tr[0])
			q.push(e.snd), M[0][e.fst - 'a'] = e.snd;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			mrk[x] |= mrk[f[x]];
			bad[x] |= bad[f[x]];
			for(int i = 0; i < E; i++) M[x][i] = M[f[x]][i];
			for(auto e : tr[x]) {
				M[x][e.fst - 'a'] = e.snd;
				int &y = f[e.snd];
				for(y = f[x]; y && !tr[y].count(e.fst); y = f[y]);
				if(tr[y].count(e.fst)) y = tr[y][e.fst];
				q.push(e.snd);
			}
		}
	}
	queue<pii> q;
	q.push(pii(0, 0)); ch[0][0] = 1;
	while(!q.empty()) {
		pii x = q.front(); q.pop();
		if(x.snd == ((1 << k) - 1)) {
			string s;
			while(x.fst || x.snd) {
				s += ch[x.fst][x.snd];
				x = ls[x.fst][x.snd];
			}
			reverse(s.begin(), s.end());
			puts(s.c_str());
			return 0;
		}
		for(i = 0; i < E; i++) {
			int y = M[x.fst][i];
			int bm = x.snd | mrk[y];
			if(bad[y] || ch[y][bm]) continue;
			ch[y][bm] = 'a' + i;
			ls[y][bm] = x;
			q.push(pii(y, bm));
		}
	}
	puts("-");
}
