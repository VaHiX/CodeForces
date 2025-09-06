/*
 * Problem URL : https://codeforces.com/contest/632/problem/B
 * Submit Date : 2025-09-04
 */

#include<stdio.h>
#include<algorithm>

#define ll long long


int main(){
    long n;
    scanf("%ld", &n);
    long a[n];
    char s[n+1];
    ll out, t=0, x=0;
    for(long i=0; i<n; i++)scanf("%ld", &a[i]);
    scanf("%*c%[^\n]", s);
    for(long i=0; i<n; i++)if(s[i]=='B')t+=a[i];
    out=t;
    for(long i=0; i<n; i++){
        if(s[i]=='B')x-=a[i];
        else x+=a[i];
        out=std::max(out, t+x);
    }
    x=0;
    for(long i=n-1; i>=0; i--){
        if(s[i]=='B')x-=a[i];
        else x+=a[i];
        out=std::max(out, t+x);
    }
    printf("%lld", out);
}
