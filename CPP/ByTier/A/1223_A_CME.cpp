/*
 * Problem URL : https://codeforces.com/contest/1223/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>
int main(){int q,n;std::cin>>q;while(q--){std::cin>>n;std::cout<<(n<3?2:(n%2?1:0))<<'\n';}}