/*
 * Problem URL : https://codeforces.com/problemset/problem/577/A
 * Submit Date : 2025-08-16
 */

#include "iostream"
int main(){int i,x,n,a=0;std::cin>>n>>x;for(i=1;i<=n;i++)if(x%i==0&&x/i<=n)a++;std::cout<<a;}