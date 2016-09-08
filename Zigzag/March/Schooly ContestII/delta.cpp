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
	int y, m, d, yy, mm, dd, k=0;
	scanf("%d%d%d%d%d%d",&y, &m, &d, &yy, &mm, &dd);
	int s=DaysInMonth(m, IsLeapYear(y));
	while (y!=yy || m!=mm || d!=dd)
	{
		d++;
		k++;
		if (d>s)
		{
			
			d=d-s;
			m++;
			if (m>12) m=m-12;
			if (m==1) y=y+1;
			s=DaysInMonth(m, IsLeapYear(y));
		}
	}
	printf("%d\n",k);
	return 0;
}