/*
 * Problem URL : https://codeforces.com/contest/616/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 string a,b;
 cin>>a>>b;

(a.length()>b.length())?b=string(a.length()-b.length(),'0')+b :a=string(b.length()-a.length(),'0')+a;

cout<<(a==b?"=":a>b?">":"<");
 
    return 0;
}
