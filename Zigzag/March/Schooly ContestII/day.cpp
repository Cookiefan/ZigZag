#include <bits/stdc++.h>
using namespace std;

int x,y,z;

bool IsLeapYear(int y)
{
	return (y%4==0 && y%100!=0)||(y%400==0);
}

int DaysInMonth(int m, int r)
{
	switch (m)
	{
		case 1:
			return 31;
		break;
		case 2:
			if (r) return 29;
			else return 28;
		break;
		case 3:
			return 31;
		break;
		case 4:
			return 30;
		break;
		case 5:
			return 31;
		break;
		case 6:
			return 30;
		break;
		case 7:
			return 31;
		break;
		case 8:
			return 31;
		break;
		case 9:
			return 30;
		break;
		case 10:
			return 31;
		break;
		case 11:
			return 30;
		break;
		case 12:
			return 31;
		break;
	}
}

int main()
{
	int y, m, d, k;
	scanf("%d%d%d%d",&y, &m, &d, &k);
	d+=k;
	int s=DaysInMonth(m, IsLeapYear(y));
	while (d>s)
	{
		d-=s;
		m=m+1;
		if (m>12) m=m-12;
		if (m==1) y=y+1;
		s=DaysInMonth(m, IsLeapYear(y));
	}
	printf("%d %d %d\n",y, m, d);
	return 0;
}