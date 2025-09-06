/*
 * Problem URL : https://codeforces.com/contest/1256/problem/C
 * Submit Date : 2025-09-04
 */

#include<iostream>
using namespace std;
int c[1001],d,i,j,k,m,n,p,q;
int main(){
    for(cin>>n>>m>>d,p=m+1,q=d-1,i=1;i<p;cin>>c[i],n-=c[i++]);
    if(n>p*q) cout<<"NO";else for(cout<<"YES\n",i=0;i<p;++i){
    for(j=0;j<c[i];++j,cout<<i<<' ');for(k=min(n,q),n-=k,j=0;j<k;++j,cout<<0<<' ');}}