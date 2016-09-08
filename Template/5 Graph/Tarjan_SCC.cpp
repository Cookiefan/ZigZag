//tarjan强连通分量
void tarjan(int now)
{
    dfn[now]=low[now]=++tim;
	stack[++top]=now;
    v[now]=1;
	for (int j=fir[now];j;j=e[j].next)
	{
		int k=e[j].t;
		if (!v[k]) tarjan(k);
		if (v[k]<2) low[now]=min(low[now],low[k]);
	}
	if (dfn[now]==low[now])
	{
		num++;
		while (stack[top+1]!=now)
		{
			web[stack[top]]=num;
			v[stack[top--]]=2;
		}
    }
}