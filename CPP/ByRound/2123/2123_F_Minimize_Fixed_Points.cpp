/*
 * Problem URL : https://codeforces.com/problemset/problem/2123/F
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;

int n,a[100010];

void solve(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        a[i] = i;
        for(int j = 2;j * j <= i;j++)
            if(i % j == 0){
                swap(a[i],a[i / j]);
                break;
            }
    }
    for(int i = 1;i <= n;i++)
        printf("%d ",a[i]);
    putchar('\n');
}

int main(){
    int t; scanf("%d",&t);
    while(t--) solve();
}