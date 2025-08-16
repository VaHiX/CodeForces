/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/A
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
	int _;cin>>_;
	while(_--){
		int n,ans=0;cin>>n;
		vector<int> a(n+10);vector<int> b(n+10);
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i],ans+=max(0,a[i]-b[i]);cout<<ans+1<<'\n';
	}
}