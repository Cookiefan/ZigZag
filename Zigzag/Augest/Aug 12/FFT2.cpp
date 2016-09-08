#include <bits/stdc++.h>
#define maxn 202000
using namespace std;
typedef complex<double> cpx;
const double pi=acos(-1.0);

int rev(int id, int len)
{
    int ret = 0;
    for(int i = 0; (1 << i) < len; i++)
    {
        ret <<= 1;
        if(id & (1 << i)) ret |= 1;
    }
    return ret;
}

cpx A[140000];
void FFT(cpx* a, int len, int DFT)//对a进行DFT或者逆DFT, 结果存在a当中
{
    //Complex* A = new Complex[len]; 这么写会爆栈
    for(int i = 0; i < len; i++)
        A[rev(i, len)] = a[i];
    for(int s = 1; (1 << s) <= len; s++)
    {
        int m = (1 << s);
        cpx wm = cpx(cos(DFT*2*pi/m), sin(DFT*2*pi/m));
        for(int k = 0; k < len; k += m)
        {
            cpx w = cpx(1, 0);
            for(int j = 0; j < (m >> 1); j++)
            {
                cpx t = w*A[k + j + (m >> 1)];
                cpx u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w*wm;
            }
        }
    }
    if(DFT == -1) for(int i = 0; i < len; i++) A[i] /= len;
    for(int i = 0; i < len; i++) a[i] = A[i];
}

char numA[50010], numB[50010];//以每一位为系数, 那么多项式长度不超过50000
cpx a[140000], b[140000];//对应的乘积的长度不会超过100000, 也就是不超过(1 << 17) = 131072
int ans[140000];
int main()
{
    while(~scanf("%s", numA))
    {
        int lenA = strlen(numA);
        int sa = 0;
        while((1 << sa) < lenA) sa++;
        scanf("%s", numB);
        int lenB = strlen(numB);
        int sb = 0;
        while((1 << sb) < lenB) sb++;
        //那么乘积多项式的次数不会超过(1 << (max(sa, sb) + 1))
        int len = (1 << (max(sa, sb) + 1));
        for(int i = 0; i < len; i++)
        {
            if(i < lenA) a[i] = cpx(numA[lenA - i - 1] - '0', 0);
            else a[i] = cpx(0, 0);
            if(i < lenB) b[i] = cpx(numB[lenB - i - 1] - '0', 0);
            else b[i] = cpx(0, 0);
        }
        FFT(a, len, 1);
        FFT(b, len, 1);//把A和B换成点值表达
        for(int i = 0; i < len; i++)//做点值表达的成乘法
            a[i] = a[i]*b[i];
        FFT(a, len, -1);//逆DFT换回原来的系数, 虚部一定是0
        for(int i = 0; i < len; i++)
            ans[i] = (int)(a[i].real() + 0.5);//取整误差的处理
        for(int i = 0; i < len - 1; i++)//进位问题
        {
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
        }
        bool flag = 0;
        for(int i = len - 1; i >= 0; i--)//注意输出格式的调整即可
        {
            if(ans[i]) printf("%d", ans[i]), flag = 1;
            else if(flag || i == 0) printf("0");
        }
        putchar('\n');
    }
    return 0;
}
