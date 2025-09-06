/*
 * Problem URL : https://codeforces.com/contest/1239/problem/A
 * Submit Date : 2025-09-02
 */

#include<stdio.h>
long long int f[100001]={0,1,2},i,m,n;int main(){for(i=3;i<=100000;i++){f[i]=(f[i-1]+f[i-2])%1000000007;}scanf("%lld%lld",&m,&n);printf("%lld",2*(f[m]+f[n]-1)%1000000007);}