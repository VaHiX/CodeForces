/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/E
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
int a[200001],b[200001],n,t;
bool f;
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	for(cin>>t;t;t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		f=a[n]==b[n];
		for(int i=n-1;i>=1;i--){
			f&=a[i]==b[i]||(a[i]^a[i+1])==b[i]||(a[i]^b[i+1])==b[i];
		}
		cout<<(f?"YES\n":"NO\n");
	}
	return 0;
}