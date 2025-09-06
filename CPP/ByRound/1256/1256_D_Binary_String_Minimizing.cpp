/*
 * Problem URL : https://codeforces.com/contest/1256/problem/D
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin>>t;
	while(t--){
		long long n,k;string s;cin>>n>>k>>s;
		long long l=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='1'){
				l++;
			}else{
			   swap(s[i],s[i-min(l,k)]);
				k-=l;
			}
			if(k<=0)break;
		}
		cout<<s<<"\n";
	}
	return 0;
}