/*
 * Problem URL : https://codeforces.com/problemset/problem/2120/C
 * Submit Date : 2025-08-14
 */

#include"bits/stdc++.h"
using namespace std;
using ll=long long;
int main(){ios::sync_with_stdio(0);cin.tie(0);
 int T;cin>>T;
 while(T--){
  int n;ll m;cin>>n>>m;
  ll mn=n,mx=1ll*n*(n+1)/2;
  if(m<mn||m>mx){cout<<"-1\n";continue;}
  int k=1;
  for(;k<=n;k++){
   ll s=1ll*k*(2ll*n-k+1)/2;
   ll d=s-m,cap=1ll*(n-k)*(k-1);
   if(d>=0&&d<=cap)break;
  }
  cout<<k<<"\n";
  vector<int> p(n+1,0);
  for(int i=1;i<k;i++)p[i]=k;
  ll d=1ll*k*(2ll*n-k+1)/2-m;
  for(int v=k+1;v<=n;v++){
   if(!d){p[v]=k;continue;}
   ll t=min<ll>(d,k-1);
   p[v]=k-t;
   d-=t;
  }
  for(int v=1;v<=n;v++)if(v!=k)cout<<v<<" "<<p[v]<<"\n";
 }
 return 0;
}
