/*
 * Problem URL : https://codeforces.com/problemset/problem/615/A
 * Submit Date : 2025-08-16
 */

#include <iostream>
int a[101],n,m,t,l,c;
main(){
    std::cin>>n>>m;
    while(n--&&std::cin>>t)while(t--)std::cin>>l,c+=(!a[l]++);
    puts((c-m)?"NO":"YES");
}