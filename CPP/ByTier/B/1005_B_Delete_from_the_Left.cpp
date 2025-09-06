/*
 * Problem URL : https://codeforces.com/contest/1005/problem/B
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
string f,s;
cin>>f>>s;
int i=f.size()-1,j=s.size()-1;
while(i>=0&&j>=0&&f[i]==s[j]){
i--;
j--;
}
cout<<i+j+2;
}