//KMP
int kmp(char *t)
{
	int n=strlen(t);
	memset(nxt,-1,sizeof(nxt));
	int j=-1;
	for (int i=1;i<n;i++)
	{
		while (j!=-1&&t[i]!=t[j+1]) j=nxt[j];
		if (t[i]==t[j+1]) j++;
		nxt[i]=j;
	}
	return n-1-nxt[n-1];//n-next[n-1]是最小循环节
}
void match(char *s, char *t)
{
	int ls=strlen(s), lt=strlen(t);
	int j=-1;
	for (int i=0;i<ls;i++)
	{
		while (j!=-1 && s[i]!=t[j+1]) j=nxt[j];
		if (s[i]==t[j+1]) j++;
	}
}