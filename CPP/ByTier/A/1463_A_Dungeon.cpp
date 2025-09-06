/*
 * Problem URL : https://codeforces.com/contest/1463/problem/A
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
int t,a,b,c,s;
int main(){
    for(scanf("%d",&t);t--;){
        scanf("%d%d%d",&a,&b,&c);s=a+b+c;
        puts((s%9||s/9>a||s/9>b||s/9>c)?"NO":"YES");
    }
}