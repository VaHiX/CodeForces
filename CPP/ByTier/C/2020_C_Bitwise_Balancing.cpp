/*
 * Problem URL : https://codeforces.com/contest/2020/problem/C
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		long long x,y,z,res;
		cin>>x>>y>>z;
		res=x^z;
		if((res|x)-(res&y)==z) cout<<res<<"\n";
		else cout<<"-1\n";
	}
}