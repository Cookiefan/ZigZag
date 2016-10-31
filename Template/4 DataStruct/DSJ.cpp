//并查集
int f[maxn];
int find(int x){
	// while (f[x]!=-1) x=f[x]=f[f[x]];
	// return x;
	return f[x]==-1?x:f[x]=find(f[x]);
}

bool merge(int x, int y){
	int fx=find(x), fy=find(y);
	if (fx!=fy){
		f[fx]=fy;
		return 1;
	}
	return 0;
}