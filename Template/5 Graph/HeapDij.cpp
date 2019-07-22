void dij(int st)
{
	memset(d, 0x3f, sizeof(d));
	memset(vis,0,sizeof(vis));
	priority_queue<pii, vector<pii>, greater<pii> > q;
	q.push(pii(0, st));
	d[st]=0;
	while (!q.empty()){
		int i=q.top().second;
		q.pop();
		if (vis[i]) continue;
		vis[i]=1;
		for (int j=fir[i];j;j=e[j].next){
			int k=e[j].t;
			if (d[i]+e[j].val<d[k]){
				d[k]=d[i]+e[j].val;
				q.push(pii(d[k], k));
			}
		}
	}
}