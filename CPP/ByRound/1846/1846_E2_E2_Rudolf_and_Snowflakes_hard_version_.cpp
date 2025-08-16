/*
 * Problem URL : https://codeforces.com/problemset/problem/1846/E2
 * Submit Date : 2025-08-13
 */

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,m,k,t;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);	
	cin>>t;
	while(t--){
		cin>>n;
		int x=0;
		int f=0;
		for(int i=2;i<=60;i++){
			k=pow(n,1.0/i);
			m=1+k;
			x=k*k;
			if(k<2)continue;
			for(int j=2;j<=i;j++){
				m+=x;
				x*=k;
			}
			if(m==n){
				f=1;
				break;
			}
		}
		if(f){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}