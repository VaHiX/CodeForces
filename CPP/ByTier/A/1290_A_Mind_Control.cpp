/*
 * Problem URL : https://codeforces.com/contest/1290/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,m,k,ans,s;
	cin>>t;
	vector<int> a;
	while(t--){
		cin>>n>>m>>k;
		ans=INT_MIN;
		a.resize(n);
		for(int i=0;i<n;i++)
		cin>>a[i];
		k=min(k,m-1);
		for(int i=0;i<=k;i++){
			s=INT_MAX;
			for(int j=0;j<(m-k);j++){
				s=min(s,max(a[i+j],a[i+j+n-m]));
			}
			ans=max(s,ans);
		}
		cout<<ans<<endl;
	}
}