/*
 * Problem URL : https://codeforces.com/contest/1255/problem/A
 * Submit Date : 2025-08-27
 */

#import<iostream>
int a,b,t;main(){for(std::cin>>t;t--;printf("%d ",a/5+(a%5+1)/2))std::cin>>a>>b,a=abs(a-b);}