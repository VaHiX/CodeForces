/*
 * Problem URL : https://codeforces.com/contest/1351/problem/C
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
int main()
{
int t;
cin>>t;
while(t--)
{ string s;
cin>>s;
set<pair<int,int>>v;
int a=0,b=0,c=0;
for(char x:s)
{ int p=a,q=b;
if(x=='N')
a++;
else if(x=='S')
a--;
else if(x=='W')
b--;
else b++;
if(v.count({p+a,q+b})==0)
c+=5,v.insert({p+a,q+b});
else c+=1;}
cout<<c<<endl;
}}