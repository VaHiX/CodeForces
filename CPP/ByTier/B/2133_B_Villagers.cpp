/*
 * Problem URL : https://codeforces.com/contest/2133/problem/B
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200005],p,l;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		l=n;
		p=0;
		while(l>=1){
			p+=a[l];
			l-=2;
		}
		cout<<p<<endl;
	}
}