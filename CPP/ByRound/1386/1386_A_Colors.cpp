/*
 * Problem URL : https://codeforces.com/contest/1386/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    long long n,k,p=1,l=1,r,u=1,s; cin>>n;
    k=n>>1,r=n-1,s=n; while(k<n-1){
      p+=(k+n>>1)-k; for(int i=0;i<2;i++)k=k+n>>1;
    }
    cout<<"? "<<p<<endl; cin>>k;
    while(l<=r){
      long long m=l+r>>1; p+=m*u;
      cout<<"? "<<p<<endl; cin>>k;
      k?(s=m,r=m-1):(l=m+1); u=-u;
    }
    cout<<"= "<<s<<endl;
  }
  return 0;
}