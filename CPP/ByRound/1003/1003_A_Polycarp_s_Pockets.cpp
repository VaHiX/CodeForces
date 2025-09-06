/*
 * Problem URL : https://codeforces.com/contest/1003/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
int a,p,b[105];
int main(){
cin>>a;
while(cin>>a)
p=max(p,++b[a]);
cout<<p;
 
}