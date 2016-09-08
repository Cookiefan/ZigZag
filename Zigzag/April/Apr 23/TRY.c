#include <stdio.h>
int ay[] = {31,28,31,30,31,30,31,31,30,31,30,31};
void Geq(int rr)
{
   if (rr % 4 == 0)
   {
        if (rr % 100 == 0)
            {
            if (rr % 400 == 0)
                ay[1] = 29;
            else
                ay[1] = 28;
            }
        else
           ay[1] = 29;
    }
    else
        ay[1] = 28;
}
int main()
{
    int yy,mm,dd,k;
    //printf("Input(year month day k):");
    scanf("%d %d %d %d",&yy,&mm,&dd,&k);
    Geq(yy);
    while (k > 0)
   {
        if (dd < ay[mm - 1])
      dd++;
        else
      {
            mm++;
            dd = 1;
        }
        if (mm > 12)
      {
            yy++;
            mm = 1;
            Geq(yy);
        }
        k--;
    }
    printf("%d %d %d\n", yy, mm, dd);
    return 0;
}