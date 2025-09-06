/*
 * Problem URL : https://codeforces.com/contest/933/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
int n,x,j,d[6];
int main(){
cin>>n;
while(n--){cin>>x;for(j=2;j<6;++j)d[j]=max(d[j-1],d[j]+(j%2+1==x));}
cout<<d[5];
}