/*
 * Problem URL : https://codeforces.com/contest/2135/problem/D1
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
const int N=11343,B=116;
int T;
signed main(){
    scanf("%d",&T);
    while(T--){
        printf("? %d ",N);for(int i=1;i<=N;i++)printf("%d ",B);fflush(stdout);
        int k,l=0,r=0;
        scanf("%d",&k);
        if(k==0){
            printf("? %d ",B*B);for(int i=1;i<=B*B;i++)printf("1 ");fflush(stdout);
            scanf("%d",&k);
            int ans=0;
            for(int i=1;i<B;i++){
                if((B*B+i-1)/i==k){
                    ans=i;
                    break;
                }
            }
            printf("! %d\n",ans);fflush(stdout);
        }else{
            for(int i=B;i<=100000;i++){
                int K=i/B;
                if((N+K-1)/K==k){
                    if(!l)l=i;r=i;
                }
            }
            printf("? %d ",r-l+1<<1);
            for(int i=1;i<=r-l+1;i++)printf("%d %d ",l,i);fflush(stdout);
            scanf("%d",&k);
            k=(r-l+1<<1)-k;
            printf("! %d\n",l+k);fflush(stdout);
        }
    }    
    return 0;
}