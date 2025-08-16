/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/C
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
void solve(){
int n;long long k;cin>>n>>k;
vector<long long>a(n),b(n);
for(int i=0;i<n;++i){long long x;cin>>x;a[i]=min(x%k,k-x%k);}
for(int i=0;i<n;++i){long long x;cin>>x;b[i]=min(x%k,k-x%k);}
sort(a.begin(),a.end());
sort(b.begin(),b.end());
if(a==b)cout<<"YES\n";else cout<<"NO\n";
}
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
int t;cin>>t;
while(t--)solve();
}
