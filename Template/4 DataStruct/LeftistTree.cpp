//左偏树
int v[maxn], dis[maxn], sz[maxn];
int l[maxn], r[maxn];
int rot[maxn], st[maxn], ed[maxn];
int num;
int build(int z){
	v[++num]=z;
	sz[num]=1;
	l[num]=r[num]=dis[num]=0;
	return num;
}
int merge(int x, int y){
	if (!x || !y) return x+y;
	if (v[x]<v[y]) swap(x, y);//bit rot
	r[x]=merge(r[x], y);
	if (dis[r[x]]>dis[l[x]]) swap(l[x], r[x]);
	sz[x]=sz[l[x]]+sz[r[x]]+1;
	dis[x]=dis[r[x]]+1;
	return x;
}
int top(int x){
	return v[x];
}
int size(int x){
	return sz[x];
}
void pop(int &x){
	x=merge(l[x], r[x]);
}