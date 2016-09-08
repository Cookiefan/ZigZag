#include <bits/stdc++.h>
using namespace std;

int w[10],h[10],l[30],r[30];

bool judge()
{
	for (int i=0;i<8;i++)
		if (w[i]>1 || h[i]>1)
			return 0;
				
	for (int i=0;i<15;i++)
		if (l[i]>1 || r[i]>1)
			return 0;

	return 1;
}

int main()
{
	int x,y;
	int Case;
	scanf("%d",&Case);
	char c[4];
	for (int o=1;o<=Case;o++)
	{
		memset(w,0,sizeof(w));
		memset(h,0,sizeof(h));
		memset(l,0,sizeof(l));
		memset(r,0,sizeof(r));
		for (int i=1;i<=8;i++)
		{
			scanf(" %s",c);
			x=c[0]-'A';
			y=c[1]-'1';
			w[x]++;
			h[y]++;
			l[x+y]++;
			r[x-y+7]++;
		}
		
		if (!judge())
			printf("Invalid\n");
		else
			printf("Valid\n");
	}
	
	return 0;
}