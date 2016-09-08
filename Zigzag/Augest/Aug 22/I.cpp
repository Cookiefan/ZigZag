#include <bits/stdc++.h>
using namespace std;
int n;


void remain(int ans, int st, int ed)
{
	printf("%d - %d\n",st,st+1);//ans+1
	for (int i=st+2;i<=ed;i++)
		printf("%d * %d\n",i,ans+i-st-1);//ans+i-st-1
	printf("%d + %d\n",ans,ans+ed-st);
}

int main()
{
	//freopen("I.in","w",stdout);
	while (scanf("%d",&n)!=EOF)
	{
		//cout<<n<<endl;
		if (n>=14)
		{
			printf("%d + %d\n",1,2);//n+1
			for (int i=3;i<=4;i++)
				printf("%d + %d\n",i,n+i-2);//n+i-1
			printf("%d / %d\n",n+3,5);//n+4
			
			printf("%d + %d\n",6,7);//n+5
			for (int i=8;i<=11;i++)
				printf("%d + %d\n",i,n+i-3);//n+i-2
			printf("%d / %d\n",n+9, 12);//n+10
			printf("%d * %d\n",n+4, n+10);//n+11
			remain(n+11, 13, n);
		}
		else if (n==13)
		{
			printf("%d + %d\n",1,2);//14
			printf("%d + %d\n",3,4);//15
			printf("%d / %d\n",15,5);//16
			printf("%d - %d\n",14,16);//17
			remain(17, 6, 13);
		}
		else if (n==12)
		{
			printf("%d + %d\n",1,2);//13
			remain(13, 3, 12);
		}
		else if (n==11)
		{
			printf("%d + %d\n",1,2);//12
			printf("%d / %d\n",12,3);//13
			printf("%d + %d\n",4,5);//14
			printf("%d + %d\n",14,13);//15
			remain(15, 6, 11);
		}
		else if (n==10)
		{
			printf("%d + %d\n",1,2);//11
			printf("%d + %d\n",3,11);//12
			printf("%d + %d\n",4,12);//13
			printf("%d / %d\n",13,5);//14
			printf("%d + %d\n",6,7);//15
			printf("%d + %d\n",14,15);//16
			remain(16, 8, 10);
		}
		else if (n==9)
		{
			printf("%d + %d\n",1,2);//10
			printf("%d + %d\n",3,10);//11
			printf("%d + %d\n",4,5);//12
			printf("%d + %d\n",6,12);//13
			printf("%d / %d\n",13,7);//14
			printf("%d - %d\n",11,14);//15
			remain(15, 8, 9);
		}
		else if (n==8)
		{
			printf("%d + %d\n",1,2);//9
			printf("%d + %d\n",3,9);//10;
			remain(10, 4, 8);
		}
		else if (n==7)
		{
			printf("%d + %d\n",1,2);//8
			printf("%d + %d\n",3,8);//9
			printf("%d + %d\n",4,5);//10
			printf("%d + %d\n",10,6);//11
			printf("%d / %d\n",11,7);//12
			printf("%d + %d\n",9,12);
		}
		else if (n==6)
		{
			printf("%d + %d\n",1,2);//7
			printf("%d + %d\n",3,7);//8
			printf("%d + %d\n",4,8);//9
			remain(9, 5, 6);
		}
		else if (n==5)
		{
			printf("%d * %d\n",1,2);//6
			printf("%d * %d\n",3,6);//7
			printf("%d - %d\n",7,4);//8
			printf("%d / %d\n",8,5);//9
		}
		else if (n==4)
		{
			printf("%d * %d\n",1,2);//5
			printf("%d + %d\n",5,3);//6
			printf("%d + %d\n",6,4);//7
		}
		else
			printf("-1\n");
	}
	return 0;
}