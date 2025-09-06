/*
 * Problem URL : https://codeforces.com/contest/923/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,ans;
int f[maxn];

int main(){
    scanf("%d",&n);
    ans=n;
    for(int i=2;i<=n;i++)
    {
        if(!f[i]){
            for(int j=2*i;j<=n;j+=i) f[j]=i;
        }

        f[i]=i-f[i]+1;
    }
    for(int i=f[n];i<=n;i++) ans=min(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
