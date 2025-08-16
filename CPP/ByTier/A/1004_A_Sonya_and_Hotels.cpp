/*
 * Problem URL : https://codeforces.com/problemset/problem/1004/A
 * Submit Date : 2025-08-14
 */

#include <iostream>
int n,m,k,l,s=2;
main() {for(std::cin>>n>>m>>n;std::cin>>k;)s+=k-n==2*m?1:k-n>2*m?2:0,n=k;std::cout<<s;}