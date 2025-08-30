/*
 * Problem URL : https://codeforces.com/contest/1360/problem/H
 * Submit Date : 2025-08-27
 */

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve(){
	int n,m;
	cin>>n>>m;
	ll a[n];
	string s;
	ll ans=((1LL<<m)-n-1)/2;
	for(int i=0;i<n;i++){
		cin>>s;
		a[i]=bitset<64>(s).to_ullong();
	}
	sort(a,a+n);
	for(auto i:a) ans+=(i<=ans);
	cout<<bitset<64>(ans).to_string().substr(64-m)<<endl;
}
int main(){
	int t; 
	cin>>t;
	while(t--) solve();
}