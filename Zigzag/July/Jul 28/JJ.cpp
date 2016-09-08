#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 40000

using namespace std;

int a[maxn];
int ans[maxn];
int len;

int bi_search(int i){  
    int left,right,mid;  
    left = 0,right = len;  
    while(left < right){  
        mid = (left + right) / 2;  
        if(ans[mid] >= a[i]) right = mid;  
        else left = mid + 1;
//        printf("%d %d %d\n",left,right,mid);
    }  
    return left;  
}
int main(){    
    int t;
    int n;    
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
            scanf("%d",&a[i]);        
        ans[1] = a[1];
        len = 1;        
        for(int i = 2; i <= n; i++){
            if(a[i] > ans[len]){
                ans[++len] = a[i];
            }            
            else{
                int pos = bi_search(i);
//                int pos = lower_bound(ans,ans+len,a[i])-ans;
//                printf("|%d|\n",pos);
                ans[pos] = a[i];
            }    
        }
        printf("%d\n",len);
    }

    return 0;
}
