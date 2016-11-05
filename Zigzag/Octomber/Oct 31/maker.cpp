#include <cstdio>  
#include <cstring>  
#include <vector>  
#include <ctime>  
#include <iostream>  
#include <cstdlib> 
#include <map>
using namespace std;  
typedef pair<int,int> pii;
map<pii, int> mp;

int main()  
{  
    freopen("Q.in","w",stdout);
    srand(time(0));  
    int T = 1;  
    cout<<T<<endl;  
    while (T--)  
    {  
        mp.clear();
        int n = 20;  
        cout<<n<<endl;  
        for (int i = 2; i <= n; ++ i)  
        {  
            int a = i, b = rand()%(i-1)+1;  
            mp[pii(a,b)]=mp[pii(b,a)]=1;
            cout << a <<" " << b<<endl;  
        }  
        while (1)  
        {  
            int a = rand()%n+1;  
            int b = rand()%n+1;  
            if (a!=b && !mp.count(pii(a,b)))  
            {  
                cout<<a<<" "<<b<<endl;  
                break;  
            }  
        }  
        int ask=rand()%100+1;  
        cout<<ask<<endl;  
        while (ask --)  
        {  
            string a[2];  
            a[0]="MODIFY";  
            a[1]="QUERY";  
            int flag = rand()%2;  
            if (flag)  
            {  
                cout<<a[0]<<" "<<rand()%n+1<<" "<<rand()%2+1<<" "<<rand()%20-10<<endl;  
            }  
            else  
            {  
                cout<<a[1]<<" "<<rand()%n+1<<" "<<rand()%2+1<<endl;  
            }  
        }  
    }  
    return 0;  
}  