/*
 * Problem URL : https://codeforces.com/contest/1349/problem/A
 * Submit Date : 2025-08-27
 */

#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long int n,l,g=0,k,a; cin>>n>>a; l=a; 
    for(long long int i=1;i<=n-1;i++){cin>>a; k=lcm(l,a); g=__gcd(g,k); l=__gcd(a,l);} cout<<g;
}