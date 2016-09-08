//set启发式合并
int merge(int x,int y)
{
	int tmp=inf;
	SIT prev,succ;
	if (s[x].size()<s[y].size()) swap(s[x],s[y]);
	for (SIT i=s[y].begin();i!=s[y].end();i++)
	{
		prev=succ=s[x].lower_bound(*i);
		if (prev!=s[x].begin()) prev--;
		if (prev!=s[x].end())	tmp=min(tmp,abs(*prev-*i));
		if (succ!=s[x].end())   tmp=min(tmp,abs(*succ-*i));
		s[x].insert(*i);
	}
	s[y].clear();
	return tmp;
}