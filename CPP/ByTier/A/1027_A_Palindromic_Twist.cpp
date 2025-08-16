/*
 * Problem URL : https://codeforces.com/problemset/problem/1027/A
 * Submit Date : 2025-08-15
 */

#include<bits/stdc++.h>
using namespace std;
int t,n,i,j,x,r;
string s;
int main()
{
for(cin>>t;t--;){
for(cin>>n>>s,r=j=0;j<n/2;j++){
x=s[j]-s[n-j-1];
r|=x!=0&&x*x!=4;
}
cout<<(r?"NO":"YES")<<endl;
}
return 0;
}
